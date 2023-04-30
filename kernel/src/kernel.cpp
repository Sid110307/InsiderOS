#include "include/kernelUtils.h"

extern "C" void _start(BootInfo * bootInfo)
{
	GDTDescriptor gdtDescriptor;
	gdtDescriptor.Size = sizeof(GDT) - 1;
	gdtDescriptor.Offset = (uint64_t)&DefaultGDT;

	LoadGDT(&gdtDescriptor);

	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	GlobalRenderer->ClearColor = COLOR_CYAN;
	GlobalRenderer->Clear();

	GlobalRenderer->Color = COLOR_RED;
	GlobalRenderer->Print("Kernel Initialized Successfully!");

	while (true);
}
