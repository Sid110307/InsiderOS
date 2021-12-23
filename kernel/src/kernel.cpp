#include "include/kernelUtils.h"

// uint8_t testBuffer[20];

extern "C" void _start(BootInfo * bootInfo)
{
	KernelInfo kernelInfo = InitializeKernel(bootInfo);
	PageTableManager* pageTableManager = kernelInfo.pageTableManager;

	BasicRenderer renderer(bootInfo->framebuffer, bootInfo->font);

	renderer.Print("Kernel Initialized Successfully!");

	while (true);
}