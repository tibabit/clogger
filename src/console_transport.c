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

#include "console_transport.h"

#include <stdlib.h>

#include "internals.h"
#include "config.h"

void file_transport_set_stream(file_transport_t *transport, FILE *stream);

console_transport_t * console_transport_new()
{
    console_transport_t *transport = file_transport_new(NULL);

    ENSURE(transport != NULL, NULL);

    file_transport_set_stream(transport, stdout);
    console_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMAT, (transport_opt_data_t)DEFAULT_LOG_FORMAT_CONSOLE);
    console_transport_setopt(transport, TRANSPORT_OPT_COLORIZE, (transport_opt_data_t)TRUE);
    console_transport_setopt(transport, TRANSPORT_OPT_NAME, (transport_opt_data_t)DEFAULT_TRANSPORT_NAME_CONSOLE);

    return transport;
}

int console_transport_setopt(console_transport_t *transport, transport_option_t option, unsigned long long int data)
{
    if (TRANSPORT_OPT_COLORIZE == option)
    {
        transport->colorize = data > 0;
        return 0;
    }

    return file_transport_setopt((file_transport_t*)transport, option, data);
}
