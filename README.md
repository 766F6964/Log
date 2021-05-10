# Log

## Overview
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Log is a compact logging library with an easy to use API, written in C.

## Features
- Various logging types (success, error, warning, info)
- Allows logging to stdout or to a file
- Flexible formatting of logging messages (printf wrapping)
- Optional prefixes:
    - Colorized logging type prefix
    - Shortform prefix
    - Timestamp prefix
- Minimal footprint (No external dependencies)


## Usage

An example demonstrating how to log formatted messages to stdout, while having time prefixes and colorized logging type prefixes:

```c
#include "log.h"

int main()
{
    // Configure logger
    log_use_time_prefix(true);
    log_use_short_prefix(false);
    log_use_colored_prefix(true);
    log_set_mode(STDOUT);

    log_info("Loading dataset with id: %d ...", 123);
    log_success("Dataset loaded successfully");

    log_info("Generating datastructure from dataset ...");
    log_warning("Data entry at offset %#08x with value: %s uses invalid offset.", 20, "test");
    log_warning("Data structure created with %d error(s)", 1);

    log_info("Serializing datastructure ...");
    log_error("Failed to serialize datastructure. Entry %d with value(s) x=%.2f y=%.2f are invalid.", 7, 10.5f, 20.5f);

    return 0;
}
```

![](https://i.imgur.com/nhpMnte.png)
