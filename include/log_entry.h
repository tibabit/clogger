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
    SEVERITY_DEBUG,          /* debug level message */
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
    string_t message;
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
