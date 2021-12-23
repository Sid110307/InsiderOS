#pragma once

#include "../lib/math.h"
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
};