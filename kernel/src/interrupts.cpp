#include "include/interrupts.h"

void PageFaultHandler(struct interruptFrame* frame)
{
	Panic("Page Fault Detected!");

	int* test = (int*)0x8000000000;
	*test = 2;

	while (true);
}

void DoubleFaultHandler(struct interruptFrame* frame)
{
	Panic("Double Faults Detected!");
	while (true);
}

void GeneralProtectionFaultHandler(struct interruptFrame* frame)
{
	Panic("General Protection Fault (Segfault) Detected!");
	while (true);
}