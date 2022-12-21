#pragma once

#include "defines.h"

void* pAllocate(uint64 size, bool aligned);

void pFree(void* block, bool aligned);

void* pZeroMemory(void* block, uint64 size);

void* pCopyMemory(void* dest, const void* source, uint64 size);

void* pSetMemory(void* dest, int32 value, uint64 size);

void pWrite(const char* message, uint8 color);

void pWriteError(const char* message, uint8 color);

ENMAPI float64 getAbsoluteTime();

void Sleep(uint64 ms);

int32 getProcessorCount();