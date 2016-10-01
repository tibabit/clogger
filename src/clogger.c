/**
 * MIT License
 * 
 * Copyright (c) 2016 Vikash Kesarwani
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
#include <stdlib.h>

#include "log_entry.h"
#include "console_transport.h"

#define COLOR(ANSI_CODE)        ("\x1b[3"#ANSI_CODE"m")
#define COLOR_GREEN		COLOR(2)
#define COLOR_RED		COLOR(1)
#define COLOR_BLUE		COLOR(4)
#define COLOR_YELLOW		COLOR(3)
#define COLOR_CYAN		COLOR(6)
#define COLOR_WHITE		COLOR(7)

#define NEWLINE     "\n"

//! private funcions

//! logging functions declarations
void clogger_log(clogger* logger, const string_t title, const string_t msg, ...);
void clogger_info(clogger* logger, const string_t msg, ...);
void clogger_warn(clogger* logger, const string_t msg, ...);
void clogger_error(clogger* logger, const string_t msg, ...);
void clogger_debug(clogger* logger, const string_t msg, ...);

void clogger_log_priv(clogger* logger,
        log_severity_t severity,
        const string_t title,
        string_t frmt,
        va_list vargs);
void clogger_add_severity(clogger *logger, log_severity_t severity, const string_t title);
void clogger_prepare_log_message(string_t *message, string_t frmt, va_list vargs);

//! logger initializer

clogger* clogger_init(void)
{
    clogger *logger = calloc(1, sizeof(clogger));
    ENSURE(logger != NULL, NULL);

    // initialize log functions
    logger->log = clogger_log;
    logger->info = clogger_info;
    logger->warn = clogger_warn;
    logger->error = clogger_error;
    logger->debug = clogger_debug;

    // add default transports
    console_transport_t * console_transport = console_transport_new();
    clogger_add_transport(logger, (transport_t *)console_transport);
    
    // add severity levels
    clogger_add_severity(logger, SEVERITY_EMERGENCY, "emerg");
    clogger_add_severity(logger, SEVERITY_ALERT, "alert");
    clogger_add_severity(logger, SEVERITY_CRITICAL, "crit");
    clogger_add_severity(logger, SEVERITY_ERROR, "error");
    clogger_add_severity(logger, SEVERITY_WARNING, "warn");
    clogger_add_severity(logger, SEVERITY_NOTICE, "notice");
    clogger_add_severity(logger, SEVERITY_INFO, "info");
    clogger_add_severity(logger, SEVERITY_DEBUG, "debug");

    // add message filter
    logger->filter = log_filter;

    return logger;
}

void clogger_destroy(clogger *logger)
{
    ASSERT(logger != NULL);

    if (logger->transports != NULL)
    {
        for (size_t i = 0; i < logger->num_transport; i++)
        {
            (logger->transports[i])->destroy(logger->transports[i]);
        }

        free(logger->transports);
    }
    if (logger->severities != NULL)
    {
        for (size_t i = 0; i < logger->severity_levels; i++)
        {
            free(logger->severities[i]);
        }

        free(logger->severities);
    }
    free(logger);
}

void clogger_add_severity(clogger *logger, log_severity_t severity, const string_t title)
{
    ASSERT(logger != NULL);
    ASSERT(title != NULL);

    logger->severities = realloc(logger->severities, sizeof(string_t) * (logger->severity_levels + 1));
    ENSURE(logger->severities != NULL);

    logger->severities[logger->severity_levels] = strdup(title);
    logger->severity_levels++;
}

void clogger_add_transport(clogger *logger, transport_t* transport)
{
    ASSERT(logger != NULL);
    ASSERT(transport != NULL);

    logger->transports = realloc(logger->transports, sizeof(transport_t*) * (logger->num_transport + 1));
    ENSURE(logger->transports != NULL);

    logger->transports[logger->num_transport] = transport;
    logger->num_transport++;
}

void clogger_log_priv(clogger* logger,
        log_severity_t severity,
        const string_t title,
        string_t frmt,
        va_list vargs)
{
    ASSERT(logger != NULL);
    ASSERT(frmt != NULL);
    ASSERT(vargs != NULL);

    log_entry_t* log_entry = log_entry_new();

    log_entry->title = title;
    log_entry->severity = severity;
    log_entry->timestamp = time(NULL);
    log_entry->catagory = logger->catagory;
    clogger_prepare_log_message(&log_entry->message, frmt, vargs);

    ENSURE(log_entry != NULL);

    for (size_t i = 0; i < logger->num_transport; i++)
    {
        if (logger->filter(logger->transports[i], log_entry)) 
        {
            (logger->transports[i])->write(logger->transports[i], log_entry);
        }
    }

    log_entry_destroy(log_entry);
}
void clogger_prepare_log_message(string_t *message, string_t frmt, va_list vargs)
{
    ASSERT(message != NULL);
    ASSERT(frmt != NULL);

    FILE* devNull = fopen("/dev/null", "w");
    ENSURE(devNull != NULL);

    va_list tempArgs;
    va_copy(tempArgs, vargs);

    size_t len = vfprintf(devNull, frmt, tempArgs) + 1;

    *message = malloc(len);
    ENSURE(*message != NULL);
    vsnprintf(*message, len, frmt, vargs);

    fclose(devNull);
}

#if 0
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
#endif

//! logging functions definitions
void clogger_log(clogger* logger, string_t title, string_t frmt, ...)
{
    ASSERT(logger != NULL);

    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_UNDEFINED, title, frmt, args); 

    va_end(args);
}

void clogger_info(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_INFO, logger->severities[SEVERITY_INFO], frmt, args); 

    va_end(args);
}

void clogger_warn(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_WARNING, logger->severities[SEVERITY_WARNING], frmt, args); 

    va_end(args);
}

void clogger_error(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_ERROR, logger->severities[SEVERITY_ERROR], frmt, args); 

    va_end(args);
}

void clogger_debug(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_DEBUG, logger->severities[SEVERITY_DEBUG], frmt, args); 

    va_end(args);
}
