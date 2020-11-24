#include "log.h"
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool time_prefix = false;
bool colored_prefix = true;
bool log_mode_file = false;
bool log_mode_stdout = false;
char *log_filename = "log.txt";

void log_use_time_prefix(bool toggle)
{
    time_prefix = toggle;
}

void log_use_colored_prefix(bool toggle)
{
    colored_prefix = toggle;
}

void log_set_filename(char *filename)
{
    log_filename = filename;
}

void log_set_mode(log_type type)
{
    if (type == 1)
    {
        log_mode_stdout = true;
        log_mode_file = false;
    }
    if (type == 2)
    {
        log_mode_stdout = false;
        log_mode_file = true;
    }
    if (type == 3)
    {
        log_mode_stdout = true;
        log_mode_file = true;
    }
}

char *__get_tag_color(char *tag)
{
    if (strcmp(tag, "INFO") == 0) { return "\033[1;34m"; }
    if (strcmp(tag, "WARN") == 0) { return "\033[1;33m"; }
    if (strcmp(tag, "PASS") == 0) { return "\033[1;32m"; }
    if (strcmp(tag, "FAIL") == 0) { return "\033[1;31m"; }

    return "\033[0m"; // Reset color
}

struct tm *__get_timestamp()
{
    time_t current_time = time((time_t *) NULL);
    struct tm *time_info = localtime(&current_time);
    return time_info;
}

log_entry *__format_log_entry(const char *tag, const char *format_string, va_list args)
{
    va_list arg_copy;
    va_copy(arg_copy, args);

    log_entry *entry = NULL;

    do
    {
        // Get size for timestamp, tag and message
        int timestamp_size = 9; // HH:MM:SS\0
        int tag_size = strlen(tag) + 1;
        int message_size = vsnprintf(NULL, 0, format_string, arg_copy) + 1;

        // Allocate memory for log_entry
        entry = (log_entry *) malloc(sizeof(log_entry));
        if (entry == NULL) { break; }

        // Allocate memory for timestamp
        entry->timestamp = (char *) malloc(timestamp_size);
        if (entry->timestamp == NULL) { break; }

        // Allocate memory for tag
        entry->tag = (char *) malloc(tag_size);
        if (entry->tag == NULL) { break; }

        // Allocate memory for message
        entry->message = (char *) malloc(message_size);
        if (entry->message == NULL) { break; }

        // Assign to struct
        strftime(entry->timestamp, timestamp_size, "%H:%M:%S", __get_timestamp());
        snprintf(entry->tag, tag_size, tag);
        vsnprintf(entry->message, message_size, format_string, args);

    } while (false);

    va_end(arg_copy);

    return entry;
}

void __write_log_to_stdout(log_entry *entry)
{
    char *color_code = __get_tag_color(entry->tag);
    char *color_reset = __get_tag_color("");

    if (time_prefix && colored_prefix)
        printf("%s %s[%s]%s %s\n", entry->timestamp, color_code, entry->tag, color_reset, entry->message);
    if (time_prefix && !colored_prefix)
        printf("%s [%s] %s\n", entry->timestamp, entry->tag, entry->message);
    if (!time_prefix && colored_prefix)
        printf("%s[%s]%s %s\n", color_code, entry->tag, color_reset, entry->message);
    if (!time_prefix && !colored_prefix)
        printf("[%s] %s\n", entry->tag, entry->message);
}

void __write_log_to_file(log_entry *entry)
{
    FILE *file = fopen(log_filename, "a");
    if (file == NULL) { exit(1); }

    if (time_prefix)
    {
        fwrite(entry->timestamp, sizeof(char), strlen(entry->timestamp), file);
        fwrite(" ", sizeof(char), 1, file);
    }

    fwrite("[", sizeof(char), 1, file);
    fwrite(entry->tag, sizeof(char), strlen(entry->tag), file);
    fwrite("] ", sizeof(char), 2, file);
    fwrite(entry->message, sizeof(char), strlen(entry->message), file);
    fwrite("\n", sizeof(char), 1, file);

    fclose(file);
}

void __log_message(const char *tag, const char *format_string, va_list args)
{
    va_list arg_copy;
    va_copy(arg_copy, args);

    log_entry *entry = __format_log_entry(tag, format_string, args);

    if (entry == NULL)
    {
        va_end(args);
        return;
    }

    if (log_mode_file) { __write_log_to_file(entry); }
    if (log_mode_stdout) { __write_log_to_stdout(entry); }

    free(entry->timestamp);
    free(entry->tag);
    free(entry->message);
    free(entry);

    va_end(args);
    fflush(stdout);
}

void log_info(const char *format_string, ...)
{
    va_list args;
    va_start(args, format_string);

    __log_message("INFO", format_string, args);

    va_end(args);
}

void log_warning(const char *format_string, ...)
{
    va_list args;
    va_start(args, format_string);

    __log_message("WARN", format_string, args);

    va_end(args);
}

void log_success(const char *format_string, ...)
{
    va_list args;
    va_start(args, format_string);

    __log_message("PASS", format_string, args);

    va_end(args);
}

void log_error(const char *format_string, ...)
{
    va_list args;
    va_start(args, format_string);

    __log_message("FAIL", format_string, args);

    va_end(args);
}
