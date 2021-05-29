#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdarg.h>

typedef struct
{
    char *tag;
    char *message;
    char *timestamp;
} log_entry;

typedef enum log_type
{
    STDOUT  = 0x1,
    LOGFILE = 0x2
} log_type;

// ToDo: Introduce some data structure to store all log_entries

/**
 * @brief Sets where the logs will be written (stdout or file)
 * @param type The log type to enable writing for
 */
void log_set_mode(log_type type);

/**
 * @brief Configure the logger to use a short prefix (e.g. [*] instead of [INFO])
 * @param toggle if true, the short prefix is used, false otherwise
 */ 
void log_use_short_prefix(bool toggle);

/**
 * @brief Configure the logger to prefix every log message with a timestamp
 * @param toggle if true, timestamp is used, false otherwise
 */
void log_use_time_prefix(bool toggle);

/**
 * @brief Configure the logger to use color highlighting for the log type.
 * @param toggle if true, color highlighting is used, false otherwise
 */
void log_use_colored_prefix(bool toggle);

/**
 * @brief Gets a pointer to the time struct for the the current time
 * @return The time struct
 */
struct tm* __get_timestamp();

/**
 * @brief Sets the name of the log file
 * @param filename The log file name
 */
void log_set_filename(char *filename);

/**
 * @brief Writes a formatted log entry to the log file, if enabled via flags
 * @param entry The log entry to write
 */
void __write_log_to_file(log_entry *entry);

/**
 * @brief Writes a formatted log entry to stdout, if enabled via flags
 * @param entry The log entry to write
 */
void __write_log_to_stdout(log_entry *entry);

/**
 * @brief Returns the ANSI color code for a given tag name.
 * @param tag The tag identifying the log type
 * @return The ANSI color code
 */
char *__get_tag_color(char *tag);

/**
 * @brief Formats all logging messages
 * @param tag The tag indicating the log type
 * @param format_string The format string holding all the variadic arguments
 * @param arg The arguments for formatting the log message
 */
log_entry *__format_log_entry(const char *tag, const char *format_string, va_list arg);

/**
 * @brief Write a formatted log message to either stdout or to a file, depending on the flags set.
 * @param tag The tag indicating the log type
 * @param format_string The format string holding all the variadic arguments
 * @param args The arguments for formatting the log message
 */
void __log_message(const char *tag ,const char *format_string, va_list args);

/**
 * @brief Print a logging message indicating a warning
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_warning(const char *format_string, ...);

/**
 * @brief Print a logging message indicating an info message
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_info(const char *format_string, ...);

/**
 * @brief Print a logging message indicating an error
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_error(const char *format_string, ...);

/**
 * @brief Print a logging message indicating a successful operation
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_success(const char *format_string, ...);

/**
 * @brief Prints a logging message indicating a critical error followed by terminating program
 * @param exitcode The exitcode that the program should be terminated with after logging the message.
 * @param format_string The unformatted string for all variadic arguments
 * @param ... The variadic arguments
 */
void log_panic(int exitcode, const char *format_string, ...);

#endif