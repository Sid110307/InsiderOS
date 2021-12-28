#include "include/pageFrameAllocator.h"

uint64_t freeMemory;
uint64_t usedMemory;
uint64_t reservedMemory;
bool isInitialized = false;
PageFrameAllocator globalAllocator;

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* memoryMap, size_t memoryMapSize, size_t memoryMapDescriptorSize)
{
	if (isInitialized) return;
	isInitialized = true;

	uint64_t memoryMapEntries = memoryMapSize / memoryMapDescriptorSize;

	void* largestFreeMemorySegment = NULL;
	size_t largestFreeMemorySegmentSize = 0;

	for (int i = 0; i < memoryMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)memoryMap + (i * memoryMapDescriptorSize));

		if (descriptor->type == 7 && descriptor->numberOfPages * EFI_PAGE_SIZE > largestFreeMemorySegmentSize)
		{
			largestFreeMemorySegment = descriptor->physicalAddress;
			largestFreeMemorySegmentSize = descriptor->numberOfPages * EFI_PAGE_SIZE;
		}
	}

	uint64_t memorySize = GetMemorySize(memoryMap, memoryMapEntries, memoryMapDescriptorSize);
	freeMemory = memorySize;

	uint64_t bitmapSize = memorySize / EFI_PAGE_SIZE / 8 + 1;
	InitBitmap(bitmapSize, largestFreeMemorySegment);

	LockPages(PageBitmap.Buffer, PageBitmap.Size / EFI_PAGE_SIZE + 1);

	for (int i = 0; i < memoryMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)memoryMap + (i * memoryMapDescriptorSize));

		if (descriptor->type != 7)
			ReservePages(descriptor->physicalAddress, descriptor->numberOfPages);
	}
}

uint64_t pageBitmapIndex = 0;

void* PageFrameAllocator::RequestPage()
{
	for (; pageBitmapIndex < PageBitmap.Size * 8; pageBitmapIndex++)
	{
		if (PageBitmap[pageBitmapIndex] == true) continue;

		LockPage((void*)(pageBitmapIndex * EFI_PAGE_SIZE));
		return (void*)(pageBitmapIndex * EFI_PAGE_SIZE);
	}

	// TODO: Page frame swapfile
	return NULL;
}

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress)
{
	PageBitmap.Size = bitmapSize;
	PageBitmap.Buffer = (uint8_t*)bufferAddress;

	for (int i = 0; i < bitmapSize; i++)
		*(uint8_t*)(PageBitmap.Buffer + i) = 0;
}

void PageFrameAllocator::FreePage(void* address)
{
	uint64_t index = (uint64_t)address / EFI_PAGE_SIZE;

	if (PageBitmap[index] == false) return;
	if (PageBitmap.Set(index, false))
	{
		freeMemory += EFI_PAGE_SIZE;
		usedMemory -= EFI_PAGE_SIZE;

		if (pageBitmapIndex > index) pageBitmapIndex = index;
	}
}

void PageFrameAllocator::FreePages(void* address, uint64_t pageCount)
{
	for (int i = 0; i < pageCount; i++)
		FreePage((void*)((uint64_t)address + (i * EFI_PAGE_SIZE)));
}

void PageFrameAllocator::LockPage(void* address)
{
	uint64_t index = (uint64_t)address / EFI_PAGE_SIZE;

	if (PageBitmap[index] == true) return;
	if (PageBitmap.Set(index, true))
	{
		freeMemory -= EFI_PAGE_SIZE;
		usedMemory += EFI_PAGE_SIZE;
	}
}

void PageFrameAllocator::LockPages(void* address, uint64_t pageCount)
{
	for (int i = 0; i < pageCount; i++)
		LockPage((void*)((uint64_t)address + (i * EFI_PAGE_SIZE)));
}

void PageFrameAllocator::ReservePage(void* address)
{
	uint64_t index = (uint64_t)address / EFI_PAGE_SIZE;

	if (PageBitmap[index] == true) return;
	if (PageBitmap.Set(index, true))
	{
		freeMemory -= EFI_PAGE_SIZE;
		reservedMemory += EFI_PAGE_SIZE;
	}
}

void PageFrameAllocator::ReservePages(void* address, uint64_t pageCount)
{
	for (int i = 0; i < pageCount; i++)
		ReservePage((void*)((uint64_t)address + (i * EFI_PAGE_SIZE)));
}

void PageFrameAllocator::UnreservePage(void* address)
{
	uint64_t index = (uint64_t)address / EFI_PAGE_SIZE;

	if (PageBitmap[index] == false) return;
	if (PageBitmap.Set(index, false))
	{
		freeMemory -= EFI_PAGE_SIZE;
		reservedMemory += EFI_PAGE_SIZE;

		if (pageBitmapIndex > index) pageBitmapIndex = index;
	}
}

void PageFrameAllocator::UnreservePages(void* address, uint64_t pageCount)
{
	for (int i = 0; i < pageCount; i++)
		UnreservePage((void*)((uint64_t)address + (i * EFI_PAGE_SIZE)));
}

uint64_t PageFrameAllocator::GetFreeRAM()
{
	return freeMemory;
}

uint64_t PageFrameAllocator::GetUsedRAM()
{
	return usedMemory;
}

uint64_t PageFrameAllocator::GetReservedRAM()
{
	return reservedMemory;
}