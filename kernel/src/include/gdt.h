#pragma once

#include <stdint.h>

struct GDTDescriptor {
	uint16_t Size;
	uint64_t Offset;
} __attribute__((packed));

struct GDTEntry {
	uint16_t LimitLow;
	uint16_t BaseLow;
	uint8_t BaseMiddle;
	uint8_t Access;
	uint8_t Flags;
	uint8_t BaseHigh;
} __attribute__((packed));

struct GDT {
	GDTEntry Null;
	GDTEntry KernelCode;
	GDTEntry KernelData;
	GDTEntry UserNull;
	GDTEntry UserCode;
	GDTEntry UserData;
} __attribute__((packed)) __attribute__((aligned(0x1000)));

extern GDT DefaultGDT;
extern "C" void LoadGDT(GDTDescriptor * gdtDescriptor);