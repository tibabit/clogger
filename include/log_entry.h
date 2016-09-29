#ifndef LOG_ENTRY_H

#define LOG_ENTRY_H

#include <time.h>
#include <stdarg.h>

#include "internals.h"

/**
 * severity levels of logs conforming to RFC5424
 */
typedef enum
{
    SEVERITY_EMERGENCY,      /* System is unusable */
    SEVERITY_ALERT,          /* Action must be taken immediately */
    SEVERITY_CRITICAL,       /* critical condition */
    SEVERITY_ERROR,          /* Error condition */
    SEVERITY_WARNING,        /* Warning conditions */
    SEVERITY_NOTICE,         /* normal but significant conditions */
    SEVERITY_INFO,           /* informational message */
    SEVERITY_DEBUG,           /* debug level message */
    SEVERITY_UNDEFINED
}log_severity_t;

/**
 * reprsents one log entry
 */
typedef struct
{
    log_severity_t severity;
    string_t title;
    time_t  timestamp;
    string_t catagory;
    va_list *msg_args;
    string_t msg_frmt;
}log_entry_t;

/**
 * create a new log entry
 */
log_entry_t* log_entry_new();

/**
 * free up all memory taken up by log_entry_t
 */
void log_entry_destroy(log_entry_t * entry);

#endif /* end of include guard: LOG_ENTRY_H */
