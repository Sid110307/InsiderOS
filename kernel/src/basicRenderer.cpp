#include "include/basicRenderer.h"

BasicRenderer* GlobalRenderer;

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* targetFont)
{
	TargetFramebuffer = targetFramebuffer;
	TargetFont = targetFont;
	Color = 0xFFFFFFFF;
	cursorPosition = { 0, 0 };
}

void BasicRenderer::DrawChar(char chr, unsigned int xOffset, unsigned int yOffset)
{
	unsigned int* pixelPointer = (unsigned int*)TargetFramebuffer->BaseAddress;
	char* fontPointer = (char*)TargetFont->glyphBuffer + (chr * TargetFont->psf1_Header->charSize);

	for (unsigned long y = yOffset; y < yOffset + 16; y++)
	{
		for (unsigned long x = xOffset; x < xOffset + 16; x++)
			if ((*fontPointer & (0b10000000 >> (x - xOffset))) > 0)
				*(unsigned int*)(pixelPointer + x + (y * TargetFramebuffer->PixelsPerScanline)) = Color;
		fontPointer++;
	}
}

void BasicRenderer::Print(const char* str)
{
	char* chars = (char*)str;

	while (*chars != 0)
	{
		DrawChar(*chars, cursorPosition.x, cursorPosition.y);
		cursorPosition.x += 8;

		if (cursorPosition.x + 8 > TargetFramebuffer->Width)
		{
			cursorPosition.x = 0;
			cursorPosition.y += 16;
		}
		chars++;
	}
}

void BasicRenderer::Clear(uint32_t color)
{
	uint64_t framebufferBaseAddress = (uint64_t)TargetFramebuffer->BaseAddress;
	uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanline * 4;
	uint64_t framebufferHeight = TargetFramebuffer->Height;
	uint64_t framebufferSize = TargetFramebuffer->BufferSize;

	for (int verticalScanline = 0; verticalScanline < framebufferHeight; verticalScanline++)
	{
		uint64_t pixelPointerBase = framebufferBaseAddress + (verticalScanline * bytesPerScanline);

		for (uint32_t* pixelPointer = (uint32_t*)pixelPointerBase; pixelPointer < (uint32_t*)(pixelPointerBase + bytesPerScanline); pixelPointer++)
			*pixelPointer = color;
	}
}

void BasicRenderer::NextLine()
{
	cursorPosition.x = 0;
	cursorPosition.y += 16;
}