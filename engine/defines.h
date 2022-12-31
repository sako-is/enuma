#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>
#include <float.h>
#include <stdbool.h>

#define INVALID_ID_U64 18446744073709551615UL
#define INVALID_ID 4294967295U
#define INVALID_ID_U16 65535U
#define INVALID_ID_U8 255U

#define typeof __typeof

#define defer(value, type, message) { goto defer; type("%s", message); return value; }

#ifdef ENM_EXPORT
	// Exports
	#ifdef _MSC_VER
		#define ENMAPI __declspec(dllexport)
	#else
		#define ENMAPI __attribute__((visibility("default")))
	#endif
#else
	// Imports
	#ifdef _MSC_VER
		/** @brief Import/export qualifier */
		#define ENMAPI __declspec(dllimport)
	#else
		/** @brief Import/export qualifier */
		#define ENMAPI
	#endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define EPLATFORM_WINDOWS 1
#ifndef _WIN64
	#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
	// Linux OS
	#define EPLATFORM_LINUX 1

#if defined(__ANDROID__)
	#define EPLATFORM_ANDROID 1
#endif

#elif defined(__unix__)
	// Catch anything not caught by the above.
	#define EPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
	// Posix
	#define EPLATFORM_POSIX 1
#elif __APPLE__
	// Apple platforms
	#define EPLATFORM_APPLE 1
	#include <TargetConditionals.h>

#if TARGET_IPHONE_SIMULATOR
	// iOS Simulator
	#define EPLATFORM_IOS 1
	#define EPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
	#define EPLATFORM_IOS 1
	// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS

#else
	#error "Unknown Apple platform"
#endif

#else
	#error "Unknown platform!"
#endif

typedef float  float32;
typedef double float64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#if defined(__clang__) || defined(__gcc__)
/** @brief Inline qualifier */
#define EINLINE __attribute__((always_inline)) inline

/** @brief No-inline qualifier */
#define ENOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)

/** @brief Inline qualifier */
#define EINLINE __forceinline

/** @brief No-inline qualifier */
#define ENOINLINE __declspec(noinline)
#else

/** @brief Inline qualifier */
#define EINLINE static inline

/** @brief No-inline qualifier */
#define ENOINLINE
#endif

/** @brief Gets the number of bytes from amount of gibibytes (GiB) (1024*1024*1024) */
#define GIBIBYTES(amount) ((amount) * 1024 * 1024 * 1024)
/** @brief Gets the number of bytes from amount of mebibytes (MiB) (1024*1024) */
#define MEBIBYTES(amount) ((amount) * 1024 * 1024)
/** @brief Gets the number of bytes from amount of kibibytes (KiB) (1024) */
#define KIBIBYTES(amount) ((amount) * 1024)

/** @brief Gets the number of bytes from amount of gigabytes (GB) (1000*1000*1000) */
#define GIGABYTES(amount) ((amount) * 1000 * 1000 * 1000)
/** @brief Gets the number of bytes from amount of megabytes (MB) (1000*1000) */
#define MEGABYTES(amount) ((amount) * 1000 * 1000)
/** @brief Gets the number of bytes from amount of kilobytes (KB) (1000) */
#define KILOBYTES(amount) ((amount) * 1000)

EINLINE uint64 get_aligned(uint64 operand, uint64 granularity) {
    return ((operand + (granularity - 1)) & ~(granularity - 1));
}

#endif