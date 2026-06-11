#include "console.h"
#include <string.h>

char console_buffer[CONSOLE_BUFFER_SIZE];
int console_buffer_end;

void DCSdebugSystemInfo(const char* str)
{
   int size = strlen(str);

   memcpy(&console_buffer[console_buffer_end], str, size);
   console_buffer_end += size;
}

