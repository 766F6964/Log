#include "../src/log.h"

int main()
{
    // Configure logger
    log_use_time_prefix(true);
    log_use_colored_prefix(true);
    log_set_mode(STDOUT);

    log_info("Loading dataset with id: %d ...", 123);
    log_success("Dataset loaded successfully");

    log_info("Generating datastructure from dataset ...");
    log_warning("Data entry at offset %#08x with value: %s uses invalid ", 20, "test");
    log_warning("Data structure created with %d error(s)", 1);

    log_info("Serializing datastructure ...");
    log_error("Failed to serialize datastructure. Entry %d with value(s) x=%.2f y=%.2f are invalid.", 7, 10.5f, 20.5f);

    return 0;
}
