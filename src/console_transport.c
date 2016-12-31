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
#include <string.h>

#include "internals.h"
#include "config.h"

void file_transport_set_stream(file_transport_t *transport, FILE *stream);
size_t file_transport_write_string(FILE* stream, string_t str);
void console_transport_write(console_transport_t *transport, log_entry_t *entry);

console_transport_t * console_transport_new()
{
    console_transport_t *transport = CALLOC(console_transport_t);

    ENSURE(transport != NULL, NULL);

    console_transport_init(transport);

    return transport;
}

void console_transport_init(console_transport_t *transport)
{
    ASSERT(transport != NULL);

    file_transport_init((file_transport_t*)transport);
    transport_t *super = (transport_t*)transport;

    super->write = (write_fn_t)console_transport_write;
    super->destroy = (destroy_fn_t)console_transport_destroy;

    file_transport_set_stream((file_transport_t*)transport, stdout);
    console_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMAT, (transport_opt_data_t)DEFAULT_LOG_FORMAT_CONSOLE);
    console_transport_setopt(transport, TRANSPORT_OPT_NAME, (transport_opt_data_t)DEFAULT_TRANSPORT_NAME_CONSOLE);

    // initialize colors
    FREE_AND_COPY(transport->color_normal, COLOR_NORMAL);
    FREE_AND_COPY(transport->colors[SEVERITY_EMERGENCY], COLOR_EMERGENCY);
    FREE_AND_COPY(transport->colors[SEVERITY_ALERT], COLOR_ALERT);
    FREE_AND_COPY(transport->colors[SEVERITY_CRITICAL], COLOR_CRITICAL);
    FREE_AND_COPY(transport->colors[SEVERITY_ERROR], COLOR_ERROR);
    FREE_AND_COPY(transport->colors[SEVERITY_WARNING], COLOR_WARNING);
    FREE_AND_COPY(transport->colors[SEVERITY_NOTICE], COLOR_NOTICE);
    FREE_AND_COPY(transport->colors[SEVERITY_INFO], COLOR_INFO);
    FREE_AND_COPY(transport->colors[SEVERITY_DEBUG], COLOR_DEBUG);

}

void console_transport_release(console_transport_t *transport)
{
    int i;
    file_transport_release(&transport->super);

    FREE_IF_NOT_NULL(transport->color_normal);
    for (i = 0; i < SEVERITY_MAX; i++)
    {
        FREE_IF_NOT_NULL(transport->colors[i]);
    }
}

void console_transport_destroy(console_transport_t *transport)
{
    ASSERT(transport != NULL);

    console_transport_release(transport);

    FREE_IF_NOT_NULL(transport);
}

void console_transport_write(console_transport_t *transport, log_entry_t *entry)
{
    ASSERT(transport != NULL);
    ASSERT(entry != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    message_buffer_t* buf = file_transport->formatter((transport_t*)file_transport, entry);
    ENSURE(buf != NULL);

    message_buffer_prepend(buf, transport->colors[entry->severity], strlen(transport->colors[entry->severity]));
    message_buffer_append(buf, transport->color_normal, strlen(transport->color_normal));
    file_transport_write_string(file_transport->stream, message_buffer_get_data(buf));

    message_buffer_destroy(buf);

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
