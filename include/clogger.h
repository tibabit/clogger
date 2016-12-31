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
 * clogger.h
 *
 *  Created on: 17-Feb-2016
 *      Author: vikash
 */

#ifndef CLOGGER_H_
#define CLOGGER_H_

#include <string.h>

#include "typedefs.h"
#include "transport.h"
#include "log_filter.h"
#include "console_transport.h"
#include "file_transport.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _clogger clogger;

/*! type definition for generic log function
 *
 * \param logger an instance of clogger
 * \param level log level(e.g.: info, debug, error)
 * \param frmt printf style format string
 * \param ... rest argument as per format
 */
typedef void (*generic_log_fn)(clogger* logger, const string_t level, const string_t frmt, ...);
/**
 * \brief type definition for level log function
 */
typedef void (*level_log_fn)(clogger* logger, const string_t, ...);

/** clogger structure
 *
 * entry point and handle of clogger instance
 */
typedef struct _clogger
{
    /** generic log function */
    generic_log_fn log;
    /** logger configurations */
    string_t catagory;
    size_t num_transport;
    transport_t **transports;

    size_t severity_levels;
    string_t *severities;

    log_filter_fn filter;
} clogger;

/**
 * \brief create an instance of clogger. In which then you can add various transports
 * to log at different places
 */
clogger* clogger_init(void);
void clogger_destroy(clogger *logger);
void clogger_add_transport(clogger *logger, transport_t* transport);
transport_t* clogger_get_transport(clogger *logger, string_t name);

//! logging functions declarations
void clogger_log    ( clogger* logger, const string_t title, const string_t frmt, ...);
void clogger_emerg  ( clogger* logger, const string_t frmt, ...);
void clogger_alert  ( clogger* logger, const string_t frmt, ...);
void clogger_crit   ( clogger* logger, const string_t frmt, ...);
void clogger_error  ( clogger* logger, const string_t frmt, ...);
void clogger_warn   ( clogger* logger, const string_t frmt, ...);
void clogger_notice ( clogger* logger, const string_t frmt, ...);
void clogger_info   ( clogger* logger, const string_t frmt, ...);
void clogger_debug  ( clogger* logger, const string_t frmt, ...);

// default logger
void clogger_logd    ( const string_t title, const string_t frmt, ...);
void clogger_emergd  ( const string_t frmt, ...);
void clogger_alertd  ( const string_t frmt, ...);
void clogger_critd   ( const string_t frmt, ...);
void clogger_errord  ( const string_t frmt, ...);
void clogger_warnd   ( const string_t frmt, ...);
void clogger_noticed ( const string_t frmt, ...);
void clogger_infod   ( const string_t frmt, ...);
void clogger_debugd  ( const string_t frmt, ...);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* CLOGGER_H_ */
