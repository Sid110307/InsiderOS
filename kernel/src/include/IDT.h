#pragma once

#include <stdint.h>

#define IDT_TA_INTERRUPT_GATE 0B10001110
#define IDT_TA_CALL_GATE 0B10001100
#define IDT_TA_TRAP_GATE 0B10001111

struct IDTDescEntry {
	uint16_t offsetLow;
	uint16_t selector;
	uint8_t ist;
	uint8_t typeAttr;
	uint16_t offsetMedium;
	uint32_t offsetHigh;
	uint32_t ignored;

	void SetOffset(uint64_t offset);
	uint64_t GetOffset();
};

struct IDTR {
	uint16_t Limit;
	uint64_t Offset;
} __attribute__((packed));