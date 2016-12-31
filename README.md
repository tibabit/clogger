# clogger

### logging library for c/c++

[![Build Status](https://travis-ci.org/tibabit/clogger.svg?branch=master)](https://travis-ci.org/tibabit/clogger)
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Dependencies](https://img.shields.io/badge/dependencies-none-orange.svg)

## Features
 - File and console transports
 - Add multiple transport of same type
 - Colorful logging on terminal
 - Supports multiple level of logging
 - Supports `printf` formatted log message
 - Easily customizable

## Installation
 - clone the repository https://github.com/tibabit/clogger.git
 - Install cmake version >= 2.6
```bash
cd /path/to/repository
mkdir bin
cd bin
cmake .. && make
```

* [Logging](#logging)
 * [Using default logger](#using-default-logger)
 * [Console transport](#console-transport)
 * [File transport](#file-transport)

### Logging
There are two ways to use logger, one is to use default logger, which prints nice log messages on the terminal, another
is to instantiate your own logger and add transports to it

### Using default logger
```C
#include "clogger.h"

int main()
{
    clogger_emergd("Emergency type log %s", "arg 1");
    clogger_alertd("Alert type log");
    clogger_critd("Ciritcal type log");
    clogger_noticed("Notice type log");
    clogger_infod("Info type log %s", "arg 1");
    clogger_warnd("Warning type log");
    clogger_errord("Error type log");
    clogger_debugd("Debug type log");

    return 0;
}

// output
emerg: Emergency type log arg 1
alert: Alert type log
crit: Ciritcal type log
notice: Notice type log
info: Info type log arg 1
warn: Warning type log
error: Error type log
```

### Console transport
```C
#include "clogger.h"

int main()
{
    // initialize/create logger
    clogger* logger = clogger_init();
    // create a console transport
    console_transport_t * console_transport = console_transport_new();
    // set log level
    console_transport_setopt(console_transport, TRANSPORT_OPT_SEVERITY, SEVERITY_DEBUG);
    // add transport to logger
    clogger_add_transport(logger, (transport_t *)console_transport);

    clogger_emerg(logger, "Emergency type log %s", "arg 1");
    clogger_alert(logger, "Alert type log");
    clogger_crit(logger, "Ciritcal type log");
    clogger_notice(logger, "Notice type log");
    clogger_info(logger, "Info type log %s", "arg 1");
    clogger_warn(logger, "Warning type log");
    clogger_error(logger, "Error type log");
    clogger_debug(logger, "Debug type log");

    clogger_destroy(logger);
}

// Output
emerg: Emergency type log arg 1
alert: Alert type log
crit: Ciritcal type log
notice: Notice type log
info: Info type log arg 1
warn: Warning type log
error: Error type log
debug: Debug type log
```

### File Transport
```C
#include "clogger.h"

int main()
 {
    clogger* logger = clogger_init();

    file_transport_t *file_transport = file_transport_new("test.log");

    clogger_add_transport(logger, (transport_t*)file_transport);

    clogger_emerg(logger, "Emergency type log %s", "arg 1");
    clogger_alert(logger, "Alert type log");
    clogger_crit(logger, "Ciritcal type log");
    clogger_notice(logger, "Notice type log");
    clogger_info(logger, "Info type log %s", "arg 1");
    clogger_warn(logger, "Warning type log");
    clogger_error(logger, "Error type log");
    clogger_debug(logger, "Debug type log");

    clogger_destroy(logger);
}

// output
2016-10-06T16:38:50Z - emerg: Emergency type log arg 1
2016-10-06T16:38:50Z - alert: Alert type log
2016-10-06T16:38:50Z - crit: Ciritcal type log
2016-10-06T16:38:50Z - notice: Notice type log
2016-10-06T16:38:50Z - info: Info type log arg 1
2016-10-06T16:38:50Z - warn: Warning type log
2016-10-06T16:38:50Z - error: Error type log
```

## TODOs
 - configuration using config file
 - file rotation
 - unit tests
 - documentation
 - default logger
 - more examples
 - more customization
