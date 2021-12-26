#pragma once

#include <stdint.h>

#define BUFFER_SIZE 256
#define MAX_DECIMAL_PLACES 30

const char* toString(uint64_t value);
const char* toString(int64_t value);

const char* toHstring(uint64_t value);
const char* toHstring(uint32_t value);
const char* toHstring(uint16_t value);
const char* toHstring(uint8_t value);

const char* toString(double value, uint8_t roundDecimal);
const char* toString(double value);