#pragma once

#include <stdint.h>

#include "../lib/math.h"
#include "../lib/colors.h"
#include "../lib/framebuffer.h"
#include "../lib/basicfonts.h"

class BasicRenderer
{
public:
	BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* targetFont);
	Point cursorPosition;
	Framebuffer* TargetFramebuffer;
	PSF1_FONT* TargetFont;
	unsigned int Color;
	void DrawChar(char chr, unsigned int xOffset, unsigned int yOffset);
	void Print(const char* str);
	void Clear(uint32_t color);
	void NextLine();
};

extern BasicRenderer* GlobalRenderer;