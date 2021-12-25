#pragma once

#include "basicRenderer.h"
#include "panic.h"

struct interruptFrame;
__attribute__((interrupt)) void PageFaultHandler(struct interruptFrame* frame);
__attribute__((interrupt)) void DoubleFaultHandler(struct interruptFrame* frame);
__attribute__((interrupt)) void GeneralProtectionFaultHandler(struct interruptFrame* frame);