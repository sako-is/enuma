#include "platform.h"

#if EPLATFORM_WINDOWS

#include "log/logger.h"

#include <windows.h>
#include <windowsx.h>  // param input extraction
#include <stdio.h>
#include <stdlib.h>

static float64 clock_frequency;
static LARGE_INTEGER start_time;

void clock_setup() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (float64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);
}

void* pAllocate(uint64 size, bool aligned) {
    return malloc(size);
}

void pFree(void *block, bool aligned) {
    free(block);
}

void* pZeroMemory(void *block, uint64 size) {
    return memset(block, 0, size);
}

void* pCopyMemory(void *dest, const void *source, uint64 size) {
    return memcpy(dest, source, size);
}

void* pSetMemory(void *dest, int32 value, uint64 size) {
    return memset(dest, value, size);
}

void consoleWrite(const char *message, uint8 color) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static uint8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(message);
    uint64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
}

void consoleWriteError(const char *message, uint8 color) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static uint8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[color]);
    OutputDebugStringA(message);
    uint64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
}

float64 getAbsoluteTime() {
    if (!clock_frequency) {
        clock_setup();
    }

    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (float64)now_time.QuadPart * clock_frequency;
}

void pSleep(uint64 ms) {
    Sleep(ms);
}

int32 getProcessorCount() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    E_INFO("%i processor cores detected.", sysinfo.dwNumberOfProcessors);
    return sysinfo.dwNumberOfProcessors;
}

#endif // if platform windows