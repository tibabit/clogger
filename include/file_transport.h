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

#ifndef FILE_TRANSPORT_H

#define FILE_TRANSPORT_H

#include <stdio.h>

#include "log_formatter.h"
#include "transport.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct file_transport
{
    /** inherited from base class */
    transport_t super;

    /** belong to this class only */
    /** formatting related */
    log_formatter_fn formatter;
    string_t log_format;
    bool_t colorize;        // whether to show colorful log (for console transport only)
    string_t colors[SEVERITY_MAX];
    string_t color_normal;

    /* stream related */
    FILE *stream;
    string_t filename;
    bool_t is_console;      // true of transport type is console
    bool_t append;          // append or create new every time
}file_transport_t;

file_transport_t * file_transport_new(string_t filename);
int file_transport_setopt(file_transport_t *transport, transport_option_t option, unsigned long data);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* end of include guard: FILE_TRANSPORT_H */
