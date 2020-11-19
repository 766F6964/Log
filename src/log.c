#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

bool time_prefix = false;
bool colored_prefix = true;

void log_use_time_prefix(bool toggle)
{
    time_prefix = toggle;
}

void log_use_colored_prefix(bool toggle)
{
    colored_prefix = toggle;
}

void __log_print_time_prefix()
{
    time_t t = time(NULL);
    if (t == -1) { return; }

    struct tm *tm = localtime(&t);
    if (tm == NULL) { return; }

    printf("%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
}

void __log_general(const char *color, const char *tag, const char *format_string, va_list *arg)
{

    // Get the length of the format string from the arg list
    va_list arg_copy;
    va_copy(arg_copy, *arg);
    int len = vsnprintf(NULL, 0, format_string, arg_copy);
    va_end(arg_copy);

    // Check if the format string is non-empty
    if (len < 0) { return; }

    // Write format string + args in buffer
    char buf[len + 1];
    len = vsnprintf(buf, sizeof(buf), format_string, *arg);
    if (len < 0) { return; }

    // Print time prefix if specified
    if (time_prefix) { __log_print_time_prefix(); }

    // Print the log message to stdout
    printf("\033[0m\033[%sm[%s]\033[0m %s\n", color, tag, buf);
}

void log_warning(const char *format_string, ...)
{
    va_list args1;
    va_start(args1, format_string);
    __log_general(colored_prefix ? "1;33" : "", "WARN", format_string, &args1);
    va_end(args1);
    fflush(stdout);
}

void log_info(const char *format_string, ...)
{
    va_list args1;
    va_start(args1, format_string);
    __log_general(colored_prefix ? "1;34" : "", "INFO", format_string, &args1);
    va_end(args1);
    fflush(stdout);
}

void log_success(const char *format_string, ...)
{
    va_list args1;
    va_start(args1, format_string);
    __log_general(colored_prefix ? "1;32" : "", "PASS", format_string, &args1);
    va_end(args1);
    fflush(stdout);
}

void log_error(const char *format_string, ...)
{
    va_list args1;
    va_start(args1, format_string);
    __log_general(colored_prefix ? "1;31" : "", "FAIL", format_string, &args1);
    va_end(args1);
    fflush(stdout);
}
