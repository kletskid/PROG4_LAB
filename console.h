#pragma once

#define CONSOLE_BUFFER_SIZE 4096
extern char console_buffer[CONSOLE_BUFFER_SIZE];
extern int console_buffer_end;

void DCSdebugSystemInfo(const char* str);

