#pragma once

#include "defines.h"

ENMAPI uint64 stringLength(const char* str);
ENMAPI char* stringDuplicate(const char* str);

ENMAPI bool stringIsEqual(const char* str1, const char* str2);

ENMAPI int32 stringFormat(char* dest, const char* fmt, ...);
ENMAPI int32 stringFormatV(char* dest, const char* fmt, void* va_listp);