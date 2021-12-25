#include "include/kernelUtils.h"

// uint8_t testBuffer[20];

extern "C" void _start(BootInfo * bootInfo)
{
	GDTDescriptor gdtDescriptor;
	gdtDescriptor.Size = sizeof(GDT) - 1;
	gdtDescriptor.Offset = (uint64_t)&DefaultGDT;

	LoadGDT(&gdtDescriptor);

	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	GlobalRenderer->Print("Kernel Initialized Successfully!");

	int* test = (int*)0x8000000000;
	*test = 2;

	while (true);
}