#pragma once
#include <stdarg.h>
#include <stdio.h>

extern char dsp_buffer[4][20];

void DSPclearDisplay();
void DSPclearLine(int line);
#define DSPshow(LINE, FMT, ...) snprintf(dsp_buffer[LINE], 20, FMT __VA_OPT__(,) __VA_ARGS__)


