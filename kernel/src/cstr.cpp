#include "include/cstr.h"

char uintToStringOutput[BUFFER_SIZE];
char intToStringOutput[BUFFER_SIZE];
char doubleToStringOutput[BUFFER_SIZE];

char hexToStringOutput64[BUFFER_SIZE];
char hexToStringOutput32[BUFFER_SIZE];
char hexToStringOutput16[BUFFER_SIZE];
char hexToStringOutput8[BUFFER_SIZE];

const char* toString(uint64_t value)
{
	uint8_t size;
	uint64_t sizeTest = value;

	while (sizeTest / 10 > 0)
	{
		sizeTest /= 10;
		size++;
	}

	uint8_t index = 0;
	while (value / 10 > 0)
	{
		uint8_t remainder = value % 10;
		value /= 10;
		uintToStringOutput[size - index] = remainder + '0';
		index++;
	}

	uint8_t remainder = value % 10;
	uintToStringOutput[size - index] = remainder + '0';
	uintToStringOutput[size + 1] = 0;

	return uintToStringOutput;
}

const char* toString(int64_t value)
{
	uint8_t isNegative = 0;

	if (value < 0)
	{
		isNegative = 1;
		value *= -1;
		intToStringOutput[0] = '-';
	}

	uint8_t size;
	uint64_t sizeTest = value;

	while (sizeTest / 10 > 0)
	{
		sizeTest /= 10;
		size++;
	}

	uint8_t index = 0;
	while (value / 10 > 0)
	{
		uint8_t remainder = value % 10;
		value /= 10;
		intToStringOutput[isNegative + size - index] = remainder + '0';
		index++;
	}

	uint8_t remainder = value % 10;
	intToStringOutput[isNegative + size - index] = remainder + '0';
	intToStringOutput[isNegative + size + 1] = 0;

	return intToStringOutput;
}

const char* toHstring(uint64_t value)
{
	uint64_t* valuePointer = &value;
	uint8_t* pointer;
	uint8_t temp;
	uint8_t size = 8 * 2 - 1;

	for (uint8_t i = 0; i < size; i++)
	{
		pointer = ((uint8_t*)valuePointer + i);
		temp = ((*pointer & 0xF0) >> 4);
		hexToStringOutput64[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
		temp = (*pointer & 0x0F);
		hexToStringOutput64[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
	}

	hexToStringOutput64[size + 1] = 0;
	return hexToStringOutput64;
}

const char* toHstring(uint32_t value)
{
	uint32_t* valuePointer = &value;
	uint8_t* pointer;
	uint8_t temp;
	uint8_t size = 4 * 2 - 1;

	for (uint8_t i = 0; i < size; i++)
	{
		pointer = ((uint8_t*)valuePointer + i);
		temp = ((*pointer & 0xF0) >> 4);
		hexToStringOutput32[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
		temp = (*pointer & 0x0F);
		hexToStringOutput32[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
	}

	hexToStringOutput32[size + 1] = 0;
	return hexToStringOutput32;
}

const char* toHstring(uint16_t value)
{
	uint16_t* valuePointer = &value;
	uint8_t* pointer;
	uint8_t temp;
	uint8_t size = 2 * 2 - 1;

	for (uint8_t i = 0; i < size; i++)
	{
		pointer = ((uint8_t*)valuePointer + i);
		temp = ((*pointer & 0xF0) >> 4);
		hexToStringOutput16[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
		temp = (*pointer & 0x0F);
		hexToStringOutput16[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
	}

	hexToStringOutput16[size + 1] = 0;
	return hexToStringOutput16;
}

const char* toHstring(uint8_t value)
{
	uint8_t* valuePointer = &value;
	uint8_t* pointer;
	uint8_t temp;
	uint8_t size = 1 * 2 - 1;

	for (uint8_t i = 0; i < size; i++)
	{
		pointer = ((uint8_t*)valuePointer + i);
		temp = ((*pointer & 0xF0) >> 4);
		hexToStringOutput8[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : '0');
		temp = (*pointer & 0x0F);
		hexToStringOutput8[size - (i * 2)] = temp + (temp > 9 ? 55 : '0');
	}

	hexToStringOutput8[size + 1] = 0;
	return hexToStringOutput8;
}

const char* toString(double value, uint8_t roundDecimal)
{
	if (roundDecimal > MAX_DECIMAL_PLACES) roundDecimal = MAX_DECIMAL_PLACES;

	char* intPointer = (char*)toString((int64_t)value);
	char* doublePointer = doubleToStringOutput;

	if (value < 0) value *= -1;

	while (*intPointer != 0)
	{
		*doublePointer = *intPointer;
		intPointer++;
		doublePointer++;
	}

	*doublePointer = '.';
	doublePointer++;

	double newValue = value - (int)value;

	for (uint8_t i = 0; i < roundDecimal; i++)
	{
		newValue *= 10;
		*doublePointer = (int)newValue + '0';
		newValue -= (int)newValue;
		doublePointer++;
	}

	*doublePointer = 0;
	return doubleToStringOutput;
}

const char* toString(double value)
{
	return toString(value, 3);
}