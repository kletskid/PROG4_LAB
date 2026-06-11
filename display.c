#include "display.h"
#include <string.h>
#include <stdio.h>

char dsp_buffer[4][21];

void DSPclearDisplay()
{
   for (int i = 0; i < 4; i++)
      memset(dsp_buffer[0], 0, 20);
}

void DSPclearLine(int line)
{
   memset(dsp_buffer[line], 0, 20);
}


