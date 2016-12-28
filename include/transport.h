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

#ifndef TRANSPORT_H

#define TRANSPORT_H

#include "log_entry.h"

#define TRANSPORT_DATE_TIME_FORMAT_MAX_SIZE         64

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _transport transport_t;
typedef struct _clogger clogger;

typedef void (*msg_writer_fn)(transport_t *transport, log_entry_t *entry);
typedef void (*destroy_transport_fn)(transport_t *transport);

typedef struct _transport
{
    msg_writer_fn write;
    destroy_transport_fn destroy;
    log_severity_t severity;
    clogger *logger;
    char datetime_format[TRANSPORT_DATE_TIME_FORMAT_MAX_SIZE];
    string_t name;
}transport_t;

typedef enum
{
    TRANSPORT_OPT_LOG_FORMATTER,
    TRANSPORT_OPT_LOG_FORMAT,
    TRANSPORT_OPT_DATETIME_FORMAT,
    TRANSPORT_OPT_NAME,
    TRANSPORT_OPT_SEVERITY,
    TRANSPORT_OPT_COLORIZE,
}transport_option_t;

transport_t* transport_new(transport_t* transport);
void transport_release(transport_t* transport);
void transport_destroy(transport_t* transport);
int transport_setopt(transport_t *transport, transport_option_t option, unsigned long long int data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* end of include guard: TRANSPORT_H */
