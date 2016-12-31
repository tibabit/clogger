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

#ifndef CONSOLE_TRANSPORT_H

#define CONSOLE_TRANSPORT_H

#include "file_transport.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct console_transport
{
    /** inherited from base class */
    file_transport_t super;

    bool_t colorize;        // whether to show colorful log (for console transport only)
    string_t colors[SEVERITY_MAX];
    string_t color_normal;
}console_transport_t;

console_transport_t * console_transport_new();
void console_transport_init(console_transport_t *transport);
void console_transport_release(console_transport_t *transport);
void console_transport_destroy(console_transport_t *transport);
int console_transport_setopt(console_transport_t *transport, transport_option_t option, transport_opt_data_t data);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif /* end of include guard: CONSOLE_TRANSPORT_H */
