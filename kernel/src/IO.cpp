#include "include/hardware/IO.h"

void outByte(uint16_t port, uint8_t value)
{
	asm volatile("outb %0, %1" :: "a"(value), "Nd"(port));
}

uint8_t inByte(uint16_t port)
{
	uint8_t byte;
	asm volatile("inb %1, %0" : "=a"(byte) : "Nd"(port));
	return byte;
}

void IOWait()
{
	asm volatile("outb %%al, $0x80" :: "a"(0));
}