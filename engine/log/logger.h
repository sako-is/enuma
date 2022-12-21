#pragma once

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release builds.
#if E_RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum LogLevel {
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARN = 2,
	LOG_LEVEL_INFO = 3,
	LOG_LEVEL_DEBUG = 4,
	LOG_LEVEL_TRACE = 5
} LogLevel;

void log_output(LogLevel level, const char* message, ...);

#ifndef E_FATAL
    #define E_FATAL(message, ...) log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#endif

#ifndef E_ERROR
	#define E_ERROR(message, ...) log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
	#define E_WARN(message, ...) log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
	#define E_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
	#define E_INFO(message, ...) log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
	#define E_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
	#define E_DEBUG(message, ...) log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
	#define E_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
	#define E_TRACE(message, ...) log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
	#define E_TRACE(message, ...)
#endif
