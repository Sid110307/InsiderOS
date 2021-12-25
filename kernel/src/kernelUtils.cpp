#include "include/kernelUtils.h"

KernelInfo kernelInfo;
PageTableManager pageTableManager = NULL;
IDTR idtr;
BasicRenderer renderer(NULL, NULL);

void PrepareMemory(BootInfo* bootInfo)
{
	uint64_t memoryMapEntries = bootInfo->memoryMapSize / bootInfo->memoryMapDescriptorSize;

	globalAllocator = PageFrameAllocator();
	globalAllocator.ReadEFIMemoryMap(bootInfo->memoryMap, bootInfo->memoryMapSize, bootInfo->memoryMapDescriptorSize);

	uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
	uint64_t kernelPages = (uint64_t)kernelSize / EFI_PAGE_SIZE + 1;

	globalAllocator.LockPages(&_KernelStart, kernelPages);

	PageTable* PML4 = (PageTable*)globalAllocator.RequestPage();
	memset(PML4, 0, 0x1000);

	pageTableManager = PageTableManager(PML4);

	for (uint64_t i = 0; i < GetMemorySize(bootInfo->memoryMap, memoryMapEntries, bootInfo->memoryMapDescriptorSize); i += 0x1000)
		pageTableManager.mapMemory((void*)i, (void*)i);

	uint64_t framebufferBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t framebufferSize = bootInfo->framebuffer->BufferSize + 0x1000;

	globalAllocator.LockPages((void*)framebufferBase, framebufferSize / 0x1000 + 1);

	for (uint64_t i = framebufferBase; i < framebufferBase + framebufferSize; i += EFI_PAGE_SIZE)
		pageTableManager.mapMemory((void*)i, (void*)i);

	asm("mov %0, %%cr3" :: "r"(PML4));

	kernelInfo.pageTableManager = &pageTableManager;
}

void PrepareInterrupts()
{
	idtr.Limit = 0x0FFF;
	idtr.Offset = (uint64_t)globalAllocator.RequestPage();

	IDTDescEntry* pageFaultInterrupt = (IDTDescEntry*)(idtr.Offset + 0xE * sizeof(IDTDescEntry));
	pageFaultInterrupt->SetOffset((uint64_t)&PageFaultHandler);
	pageFaultInterrupt->typeAttr = IDT_TA_INTERRUPT_GATE;
	pageFaultInterrupt->selector = 0x08;

	IDTDescEntry* doubleFaultInterrupt = (IDTDescEntry*)(idtr.Offset + 0x8 * sizeof(IDTDescEntry));
	doubleFaultInterrupt->SetOffset((uint64_t)&DoubleFaultHandler);
	doubleFaultInterrupt->typeAttr = IDT_TA_INTERRUPT_GATE;
	doubleFaultInterrupt->selector = 0x08;

	IDTDescEntry* generalProtectionFaultInterrupt = (IDTDescEntry*)(idtr.Offset + 0xD * sizeof(IDTDescEntry));
	generalProtectionFaultInterrupt->SetOffset((uint64_t)&GeneralProtectionFaultHandler);
	generalProtectionFaultInterrupt->typeAttr = IDT_TA_INTERRUPT_GATE;
	generalProtectionFaultInterrupt->selector = 0x08;

	asm("lidt %0" :: "m"(idtr));
}

KernelInfo InitializeKernel(BootInfo* bootInfo)
{
	renderer = BasicRenderer(bootInfo->framebuffer, bootInfo->font);
	GlobalRenderer = &renderer;

	PrepareMemory(bootInfo);
	memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

	PrepareInterrupts();

	return kernelInfo;
}