#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdarg.h>

/**
 * Configure the logger to prefix every log message with a timestamp
 * @param toggle if true, timestamp is used, false otherwise
 */
void log_use_time_prefix(bool toggle);

/**
 * Configure the logger to use color highlighting for the log type.
 * @param toggle if true, color highlighting is used, false otherwise
 */
void log_use_colored_prefix(bool toggle);

/**
 * Prints the current timestamp with the format hh:mm:ss
 */
void __log_print_time_prefix();

/**
 * Formats all logging messages
 * @param color The color code to use, if color highlighting is enabled
 * @param tag The tag indicating the log type
 * @param format_string The format string holding all the variadic arguments
 * @param arg The arguments for formatting the log message
 */
void __log_general(const char *color, const char *tag, const char *format_string, va_list *arg);

/**
 * Print a logging message indicating a warning
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_warning(const char *format_string, ...);

/**
 * Print a logging message indicating an info message
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_info(const char *format_string, ...);

/**
 * Print a logging message indicating an error
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_error(const char *format_string, ...);

/**
 * Print a logging message indicating a successful operation
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_success(const char *format_string, ...);

#endif