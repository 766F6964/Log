#include "log.h"

int main()
{
    log_use_time_prefix(true);
    log_use_colored_prefix(true);
    log_set_mode(LOGFILE | STDOUT);

    log_info("Loading level: %#x ...", 5);
    log_warning("Level might be in an unstable state!");
    log_error("Failed to load old spawn. Setting new spawn position to x=%.2f y=%.2f", 10.5f, 20.5f);
    log_success("Loaded level successfully. Location: %s", "Hell");

    return 0;
}