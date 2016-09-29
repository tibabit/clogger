/*
 * clogger.h
 *
 *  Created on: 17-Feb-2016
 *      Author: vikash
 */

#ifndef CLOGGER_H_
#define CLOGGER_H_

#include <string.h>

#include "internals.h"
#include "transport.h"

typedef struct _clogger clogger;

typedef void (*generic_log_fn)(clogger* logger, const string_t, const string_t, ...);
typedef void (*level_log_fn)(clogger* logger, const string_t, ...);

typedef struct _clogger
{
    /** logging functions */
    generic_log_fn log;
    level_log_fn info;
    level_log_fn warn;
    level_log_fn error;
    level_log_fn debug;

    /** logger configurations */
    string_t catagory;
    size_t num_transport;
    transport_t **transports;

    size_t severity_levels;
    string_t *severities;
} clogger;

clogger* clogger_init(void);
void clogger_destroy(clogger *logger);
void clogger_add_transport(clogger *logger, transport_t* transport);

#endif /* CLOGGER_H_ */
