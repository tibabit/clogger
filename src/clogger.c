/*
 * clogger.c
 *
 *  Created on: 17-Feb-2016
 *      Author: vikash
 */

#include "clogger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define COLOR(ANSI_CODE)        ("\x1b[3"#ANSI_CODE"m")
#define COLOR_GREEN		COLOR(2)
#define COLOR_RED		COLOR(1)
#define COLOR_BLUE		COLOR(4)
#define COLOR_YELLOW		COLOR(3)
#define COLOR_CYAN		COLOR(6)
#define COLOR_WHITE		COLOR(7)

#define NEWLINE     "\n"


typedef struct _LoggerConfig
{
    char *hint;
    char *color;
}LoggerConfig;

//! global clogger object
clogger logger;

LoggerConfig config[10];

//! private funcions

//! logging functions declarations
void clogger_log(LogLevel level, string_t msg, ...);
void clogger_info(string_t msg, ...);
void clogger_warn(string_t msg, ...);
void clogger_error(string_t msg, ...);
void clogger_debug(string_t msg, ...);

void clogger_config_level(LogLevel level, char * hint, char* color);

//! logger initializer

void clogger_init(void)
{
    // initialize log functions
    logger.log = clogger_log;
    logger.info = clogger_info;
    logger.warn = clogger_warn;
    logger.error = clogger_error;
    logger.debug = clogger_debug;

    // initialize color tables
    clogger_config_level(INFO, 	    "info", 	COLOR_GREEN);
    clogger_config_level(WARNING,   "warn", 	COLOR_YELLOW);
    clogger_config_level(ERROR,     "error", 	COLOR_RED);
    clogger_config_level(DEBUG,     "debug",    COLOR_CYAN);
}

void clogger_config_level(LogLevel level, char * hint, char* color)
{
    config[level].hint = strdup(hint);
    config[level].color = strdup(color);
}

void clogger_log_priv(LogLevel level, string_t frmt, va_list vargs)
{

    // set color for the line
    printf("%s%s%s:%s ",
            config[level].color,
            config[level].hint,
            COLOR_WHITE,
            config[level].color);
    // print log message
    vprintf(frmt, vargs);
    printf(NEWLINE);
    // reset terminal color
    printf("%s", COLOR_WHITE);
}

//! logging functions definitions
void clogger_log(LogLevel level, string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(level, frmt, args); 

    va_end(args);
}

void clogger_info(string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(INFO, frmt, args); 

    va_end(args);
}

void clogger_warn(string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(WARNING, frmt, args); 

    va_end(args);
}

void clogger_error(string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(ERROR, frmt, args); 

    va_end(args);
}

void clogger_debug(string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(DEBUG, frmt, args); 

    va_end(args);
}
