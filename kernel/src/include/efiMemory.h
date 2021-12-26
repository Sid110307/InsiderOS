#pragma once

#include <stdint.h>

#define EFI_PAGE_SIZE 4096

struct EFI_MEMORY_DESCRIPTOR {
	uint32_t type;
	void* physicalAddress;
	void* virtualAddress;
	uint64_t numberOfPages;
	uint64_t attributes;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];