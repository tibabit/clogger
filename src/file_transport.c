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

#include "file_transport.h"

#include <string.h>

#include "log_formatter.h"

typedef struct _file_transport
{
    /** inherited from base class */
    msg_writer_fn write;
    destroy_transport_fn destroy;
    log_severity_t severity;

    /** belong to this class only */
    log_formatter_fn formatter;
    string_t log_format;
    FILE *stream;
    bool_t colorize;        // where to show colorful log (for console transport only)
}file_transport_t;

#include <stdlib.h>

#include "internals.h"
#include "config.h"

/**
 *
 * private functions
 *
 */
void file_transport_write(transport_t *transport, log_entry_t *entry);
void file_transport_destory(transport_t *transport);

void file_transport_set_stream(file_transport_t *transport, FILE *stream);

file_transport_t * file_transport_new()
{
    file_transport_t *transport = calloc(1, sizeof(file_transport_t));

    ENSURE(transport != NULL, NULL);

    transport->write = file_transport_write;
    transport->destroy = file_transport_destory;
    transport->severity = DEFAULT_LOG_SEVERITY;

    file_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMATTER, log_formatter_format);
    file_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMAT, DEFAULT_LOG_FORMAT_FILE);

    return transport;
}

void file_transport_write(transport_t *transport, log_entry_t *entry)
{
    ASSERT(transport != NULL);
    ASSERT(entry != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    string_t formatted_log = file_transport->formatter(file_transport->log_format, entry);
    ENSURE(formatted_log != NULL);

    fprintf(file_transport->stream, "%s\n", formatted_log);

    free(formatted_log);
}

void file_transport_destory(transport_t *transport)
{
    ASSERT(transport != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    FREE_IF_NOT_NULL(file_transport->log_format);

    if (file_transport->stream != NULL)
    {
        fclose(file_transport->stream);
    }

    free(transport);

}

void file_transport_set_stream(file_transport_t *transport, FILE *stream)
{
    ASSERT(transport != NULL);
    ASSERT(stream != NULL);

    transport->stream = stream;
}

int file_transport_setopt(file_transport_t *transport, transport_option_t option, void *data)
{
    ASSERT(transport != NULL, -1);
    if (TRANSPORT_OPT_LOG_FORMATTER == option)
    {
        ASSERT(data != NULL, -1);
        transport->formatter = (log_formatter_fn)data;
        return 0;
    }
    else if (TRANSPORT_OPT_LOG_FORMAT == option)
    {
        ASSERT(data != NULL, -1);
        FREE_AND_COPY(transport->log_format, data);
        return 0;
    }
    else if (TRANSPORT_OPT_SEVERITY == option)
    {
        transport->severity = (log_severity_t)data;
        return 0;
    }
    else if (TRANSPORT_OPT_COLORIZE == option)
    {
        transport->colorize = data > 0;
        return 0;
    }
    return -1;
}
