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

#include "internals.h"
#include "log_entry.h"
#include "console_transport.h"

// to be only used as default logger
clogger* default_logger;

//! private funcions

void clogger_log_priv(clogger* logger,
        log_severity_t severity,
        const string_t title,
        string_t frmt,
        va_list* vargs);
void clogger_add_severity(clogger *logger, log_severity_t severity, const string_t title);
void clogger_prepare_log_message(string_t *message, string_t frmt, va_list* vargs);
clogger* clogger_default(void);

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

    // add log formaatter

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

clogger* clogger_default(void)
{
    if (default_logger != NULL)
    {
        return default_logger;
    }
    default_logger = clogger_init();

    ENSURE(default_logger != NULL, NULL);

    // add default transports
    console_transport_t * console_transport = console_transport_new();
    clogger_add_transport(default_logger, (transport_t *)console_transport);

    return default_logger;
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

    FREE_AND_COPY(logger->severities[logger->severity_levels], title);
    logger->severity_levels++;
}

void clogger_add_transport(clogger *logger, transport_t* transport)
{
    ASSERT(logger != NULL);
    ASSERT(transport != NULL);

    logger->transports = realloc(logger->transports, sizeof(transport_t*) * (logger->num_transport + 1));
    ENSURE(logger->transports != NULL);
    transport->logger = logger;

    logger->transports[logger->num_transport] = transport;
    logger->num_transport++;
}

transport_t* clogger_get_transport(clogger *logger, string_t name)
{
    ASSERT(logger != NULL, NULL);
    ASSERT(name != NULL, NULL);
    size_t i;
    for (i = 0; i < logger->num_transport; i++)
    {
        if (EQUALS(name, logger->transports[i]->name))
        {
            return logger->transports[i];
        }
    }

    return NULL;
}

void clogger_log_priv(clogger* logger,
        log_severity_t severity,
        const string_t title,
        string_t frmt,
        va_list* vargs)
{
    ASSERT(logger != NULL);
    ASSERT(frmt != NULL);
    ASSERT(vargs != NULL);

    log_entry_t* log_entry = log_entry_new();

    log_entry->title = title;
    log_entry->severity = severity;
    log_entry->timestamp = time(NULL);
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
void clogger_prepare_log_message(string_t *message, string_t frmt, va_list* vargs)
{
    ASSERT(message != NULL);
    ASSERT(frmt != NULL);

    FILE* devNull = fopen("/dev/null", "w");
    ENSURE(devNull != NULL);

    vasprintf(message, frmt, *vargs);

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

    clogger_log_priv(logger, SEVERITY_UNDEFINED, title, frmt, &args);

    va_end(args);
}

void clogger_info(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_INFO, logger->severities[SEVERITY_INFO], frmt, &args);

    va_end(args);
}

void clogger_warn(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_WARNING, logger->severities[SEVERITY_WARNING], frmt, &args);

    va_end(args);
}

void clogger_error(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_ERROR, logger->severities[SEVERITY_ERROR], frmt, &args);

    va_end(args);
}

void clogger_debug(clogger* logger, string_t frmt, ...)
{
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_DEBUG, logger->severities[SEVERITY_DEBUG], frmt, &args);

    va_end(args);
}
void clogger_emerg(clogger* logger, const string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_EMERGENCY, logger->severities[SEVERITY_EMERGENCY], frmt, &args);

    va_end(args);
}

void clogger_alert(clogger* logger, const string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_ALERT, logger->severities[SEVERITY_ALERT], frmt, &args);

    va_end(args);
}

void clogger_crit(clogger* logger, const string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_CRITICAL, logger->severities[SEVERITY_CRITICAL], frmt, &args);

    va_end(args);
}

void clogger_notice(clogger* logger, const string_t frmt, ...)
{
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_NOTICE, logger->severities[SEVERITY_NOTICE], frmt, &args);

    va_end(args);
}

//==============================================================================
// Default logging
//==============================================================================
void clogger_logd(string_t title, string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);

    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_UNDEFINED, title, frmt, &args);

    va_end(args);
}

void clogger_infod(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_INFO, logger->severities[SEVERITY_INFO], frmt, &args);

    va_end(args);
}

void clogger_warnd(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_WARNING, logger->severities[SEVERITY_WARNING], frmt, &args);

    va_end(args);
}

void clogger_errord(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_ERROR, logger->severities[SEVERITY_ERROR], frmt, &args);

    va_end(args);
}

void clogger_debugd(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_DEBUG, logger->severities[SEVERITY_DEBUG], frmt, &args);

    va_end(args);
}
void clogger_emergd(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_EMERGENCY, logger->severities[SEVERITY_EMERGENCY], frmt, &args);

    va_end(args);
}

void clogger_alertd(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_ALERT, logger->severities[SEVERITY_ALERT], frmt, &args);

    va_end(args);
}

void clogger_critd(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_CRITICAL, logger->severities[SEVERITY_CRITICAL], frmt, &args);

    va_end(args);
}

void clogger_noticed(string_t frmt, ...)
{
    clogger* logger = clogger_default();
    ASSERT(logger != NULL);
    va_list args;
    va_start(args, frmt);

    clogger_log_priv(logger, SEVERITY_NOTICE, logger->severities[SEVERITY_NOTICE], frmt, &args);

    va_end(args);
}
