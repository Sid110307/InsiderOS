#pragma once

#include <stddef.h>
#include "../lib/framebuffer.h"

#include "basicRenderer.h"
#include "cstr.h"
#include "efiMemory.h"
#include "memory.h"
#include "bitmap.h"
#include "pageFrameAllocator.h"
#include "pageMapIndexer.h"
#include "pageTableManager.h"
#include "paging.h"

struct BootInfo {
	Framebuffer* framebuffer;
	PSF1_FONT* font;
	EFI_MEMORY_DESCRIPTOR* memoryMap;
	uint64_t memoryMapSize;
	uint64_t memoryMapDescriptorSize;
};

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
	PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* bootInfo);