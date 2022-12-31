#include "strings.h"

#include "defines.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>  // isspace

#ifndef _MSC_VER
#include <strings.h>
#endif

uint64 stringLength(const char* str) {
    return strlen(str);
}

char* stringDuplicate(const char* str) {
    uint64 length = stringLength(str);
    char* copy = malloc(length + 1);
    memcpy(copy, str, length);
    copy[length] = 0;
    return copy;
}

char* stringCopy(char* dest, const char* src) {
    return strncpy(dest, src, sizeof(&dest));
}

int32 stringFormat(char* dest, const char* fmt, ...) {
    if (dest) {
        __builtin_va_list arg_ptr;
        va_start(arg_ptr, fmt);
        int32 written = stringFormatV(dest, fmt, arg_ptr);
        va_end(arg_ptr);
        return written;
    }
    return -1;
}

bool stringIsEqual(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

int32 stringFormatV(char* dest, const char* fmt, void* va_listp) {
    if (dest) {
        // Big, but can fit on the stack.
        char buffer[32000];
        int32 written = vsnprintf(buffer, 32000, fmt, va_listp);
        buffer[written] = 0;
        memcpy(dest, buffer, written + 1);

        return written;
    }
    return -1;
}