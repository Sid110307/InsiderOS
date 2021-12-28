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

void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t typeAttribute, uint8_t selector)
{
	IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
	interrupt->SetOffset((uint64_t)handler);
	interrupt->typeAttr = typeAttribute;
	interrupt->selector = selector;
}

void PrepareInterrupts()
{
	idtr.Limit = 0x0FFF;
	idtr.Offset = (uint64_t)globalAllocator.RequestPage();

	SetIDTGate((void*)PageFaultHandler, 0xE, IDT_TA_INTERRUPT_GATE, 0x08);
	SetIDTGate((void*)DoubleFaultHandler, 0x8, IDT_TA_INTERRUPT_GATE, 0x08);
	SetIDTGate((void*)GeneralProtectionFaultHandler, 0xD, IDT_TA_INTERRUPT_GATE, 0x08);
	SetIDTGate((void*)KeyboardInterruptHandler, 0x21, IDT_TA_INTERRUPT_GATE, 0x08);
	SetIDTGate((void*)MouseInterruptHandler, 0x2C, IDT_TA_INTERRUPT_GATE, 0x08);

	asm("lidt %0" :: "m"(idtr));

	RemapPIC();

	outByte(PIC1_DATA, 0b11111101);
	outByte(PIC2_DATA, 0b11111111);

	asm("sti");
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