#include "logger.h"

#include "core/strings.h"
#include "platform/platform.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

void log_output(LogLevel level, const char* message, ...) {
	// TODO: These string operations are all pretty slow. This needs to be
	// moved to another thread eventually, along with the file writes, to
	// avoid slowing things down while the engine is trying to run.
	const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]:  ", "[INFO]:  ", "[DEBUG]: ", "[TRACE]: "};
    const char* colour_strings[6] = {"0;41", "1;31", "1;33", "1;32", "1;34", "1;30"};
	bool is_error = level < LOG_LEVEL_WARN;

	// Technically imposes a 32k character limit on a single log entry, but...
	// DON'T DO THAT!
	char out_message[32000];
	memset(out_message, 0, sizeof(out_message));

	// Format original message.
	// NOTE: Oddly enough, MS's headers override the GCC/Clang va_list type with a "typedef char* va_list" in some
	// cases, and as a result throws a strange error here. The workaround for now is to just use __builtin_va_list,
	// which is the type GCC/Clang's va_start expects.
	__builtin_va_list arg_ptr;
	va_start(arg_ptr, message);
	stringFormatV(out_message, message, arg_ptr);
	va_end(arg_ptr);

	// Prepend log level to message.
	stringFormat(out_message, "%s%s\n", level_strings[level], out_message);

	// Print accordingly
	if (is_error) {
        pWriteError(out_message, level);
	} else {
        pWrite(out_message, level);
	}
}