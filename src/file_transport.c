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
    /** formatting related */
    log_formatter_fn formatter;
    string_t log_format;
    bool_t colorize;        // where to show colorful log (for console transport only)
    string_t colors[SEVERITY_MAX];
    string_t color_normal;

    /* stream related */
    FILE *stream;
    bool_t is_console;      // true of transport type is console
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

    if (file_transport->colorize && file_transport->is_console)
    {
        fprintf(file_transport->stream, "%s%s%s"NEWLINE, file_transport->colors[entry->severity],
                formatted_log,
                file_transport->color_normal);
    }
    else
    {
        fprintf(file_transport->stream, "%s\n", formatted_log);
    }

    free(formatted_log);
}

void file_transport_destory(transport_t *transport)
{
    ASSERT(transport != NULL);
    int i = 0;

    file_transport_t *file_transport = (file_transport_t *)transport;

    FREE_IF_NOT_NULL(file_transport->log_format);

    FREE_IF_NOT_NULL(file_transport->color_normal);
    for (i = 0; i < SEVERITY_MAX; i++)
    {
        FREE_IF_NOT_NULL(file_transport->colors[i]);
    }

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

    if (stream == stdout)
    {
        transport->is_console = TRUE;
    }
    transport->stream = stream;
}

int file_transport_setopt(file_transport_t *transport, transport_option_t option, unsigned long data)
{
    ASSERT(transport != NULL, -1);
    if (TRANSPORT_OPT_LOG_FORMATTER == option)
    {
        ASSERT((void*)data != NULL, -1);
        transport->formatter = (log_formatter_fn)data;
        return 0;
    }
    else if (TRANSPORT_OPT_LOG_FORMAT == option)
    {
        ASSERT((void*)data != NULL, -1);
        FREE_AND_COPY(transport->log_format, (string_t)data);
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
