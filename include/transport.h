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
typedef unsigned long long int transport_opt_data_t;

typedef enum
{
    TRANSPORT_OPT_LOG_FORMATTER,
    TRANSPORT_OPT_LOG_FORMAT,
    TRANSPORT_OPT_DATETIME_FORMAT,
    TRANSPORT_OPT_NAME,
    TRANSPORT_OPT_SEVERITY,
    TRANSPORT_OPT_COLORIZE,
}transport_option_t;

typedef void (*write_fn_t)(transport_t *, log_entry_t *);
typedef void (*destroy_fn_t)(transport_t *);
typedef int (*setopt_fn_t)(transport_t *, transport_option_t, transport_opt_data_t);


typedef struct _transport
{
    log_severity_t severity;
    clogger *logger;
    char datetime_format[TRANSPORT_DATE_TIME_FORMAT_MAX_SIZE];
    string_t name;

    write_fn_t write;
    destroy_fn_t destroy;
    setopt_fn_t setopt;
}transport_t;



transport_t* transport_new();
void transport_init(transport_t* transport);
void transport_release(transport_t* transport);
void transport_destroy(transport_t* transport);
int transport_setopt(transport_t *transport, transport_option_t option, transport_opt_data_t data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* end of include guard: TRANSPORT_H */
