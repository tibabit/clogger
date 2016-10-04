# clogger

### logging library for c/c++

[![Build Status](https://travis-ci.org/tibabit/clogger.svg?branch=master)](https://travis-ci.org/tibabit/clogger) ![License](https://img.shields.io/badge/license-MIT-blue.svg)

### Features
 - Colorful logging on terminal
 - Supports multiple level of logging
 - No setup required, ready to use
 - Supports C formatted log message

### Usage

 - Copy `clogger.c` and `clogger.h` to your project directory
 - Inlcude `clogger.h` in your main file and call `clogger_init()`
 - To use logger call logging functions `logger.info`, `logger.error`, `logger.warn` or `logger.debug`

### Example

```C
#include "clogger.h"

int main()
{
    clogger_init();

    logger.info("Info type log %s", "arg 1");
    logger.warn("Warning type log");
    logger.error("Error type log");
    logger.debug("Debug type log");

}
```
### Output
```C
info: Info type log arg 1
warn: Warning type log
error: Error type log
debug: Debug type log
```
