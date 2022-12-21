#include "platform.h"

#define _POSIX_C_SOURCE 200809L

#if EPLATFORM_LINUX

#include <sys/time.h>
#include <pthread.h>
#include <errno.h>        // For error reporting
#include <sys/sysinfo.h>  // Processor info

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "log/logger.h"

#if _POSIX_C_SOURCE >= 199309L
#include <time.h>  // nanosleep
#else
#include <unistd.h>  // usleep
#endif

void* pAllocate(uint64 size, bool aligned) {
    return malloc(size);
}
void pFree(void* block, bool aligned) {
    free(block);
}
void* pZeroMemory(void* block, uint64 size) {
    return memset(block, 0, size);
}
void* pCopyMemory(void* dest, const void* source, uint64 size) {
    return memcpy(dest, source, size);
}
void* pSetMemory(void* dest, int32 value, uint64 size) {
    return memset(dest, value, size);
}

void pWrite(const char* message, uint8 color) {
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    const char* color_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", color_strings[color], message);
    printf("\033[%sm%s\033[0m", color_strings[1], "");
}
void pWriteError(const char* message, uint8 color) {
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    const char* color_strings[] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
    printf("\033[%sm%s\033[0m", color_strings[color], message);
    printf("\033[%sm%s\033[0m", color_strings[1], "");
}

float64 getAbsoluteTime() {
    struct timespec now;
    #if _POSIX_C_SOURCE >= 199309L
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
    #else
    E_ERROR("not work :("); return false; 
    #endif
}

void Sleep(uint64 ms) {
#if _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000 * 1000;
    nanosleep(&ts, 0);
#else
    if (ms >= 1000) sleep(ms / 1000);
    usleep((ms % 1000) * 1000);
#endif
}

int32 getProcessorCount() {
    // Load processor info.
    int32 processor_count = get_nprocs_conf();
    int32 processors_available = get_nprocs();
    E_INFO("%i processor cores detected, %i cores available.", processor_count, processors_available);
    return processors_available;
}

#endif // if platform linux