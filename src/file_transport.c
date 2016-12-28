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
#include <stdlib.h>

#include "internals.h"
#include "config.h"

/**
 *
 * private functions
 *
 */
void file_transport_write(transport_t *transport, log_entry_t *entry);
void file_transport_destory(file_transport_t *transport);
size_t file_transport_write_string(FILE* stream, string_t str);

void file_transport_set_stream(file_transport_t *transport, FILE *stream);

file_transport_t * file_transport_new(string_t filename)
{
    file_transport_t *transport = calloc(1, sizeof(file_transport_t));

    ENSURE(transport != NULL, NULL);

    transport_new(&transport->super);

    transport->super.write = file_transport_write;
    transport->super.destroy = file_transport_destory;
    transport->super.severity = DEFAULT_LOG_SEVERITY;
    transport->append = TRUE;

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

    file_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMATTER, (unsigned long)log_formatter_format);
    file_transport_setopt(transport, TRANSPORT_OPT_LOG_FORMAT, (unsigned long)DEFAULT_LOG_FORMAT_FILE);
    file_transport_setopt(transport, TRANSPORT_OPT_DATETIME_FORMAT, (unsigned long)DEFAULT_DATETIME_FORMAT);
    file_transport_setopt(transport, TRANSPORT_OPT_NAME, (unsigned long)DEFAULT_TRANSPORT_NAME_FILE);

    if (filename != NULL)
    {
        // open file for writing log
        transport->stream = fopen(filename, transport->append ? "a" : "w");
        if (transport->stream == NULL)
        {
            goto error;
        }
        FREE_AND_COPY(transport->filename, filename);
    }
    return transport;

error:
    file_transport_destory(transport);
    return NULL;
}

void file_transport_release(file_transport_t* file_transport)
{
    int i = 0;

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
    FREE_IF_NOT_NULL(file_transport->filename);

    transport_release((transport_t*)file_transport);
}
void file_transport_destory(file_transport_t *file_transport)
{
    ASSERT(file_transport != NULL);

    file_transport_release(file_transport);

    free(file_transport);
}

void file_transport_write(transport_t *transport, log_entry_t *entry)
{
    ASSERT(transport != NULL);
    ASSERT(entry != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    message_buffer_t* buf = file_transport->formatter((transport_t*)file_transport, entry);
    ENSURE(buf != NULL);

    if (file_transport->colorize && file_transport->is_console)
    {
        file_transport_write_string(file_transport->stream, file_transport->colors[entry->severity]);
        file_transport_write_string(file_transport->stream, message_buffer_get_data(buf));
        file_transport_write_string(file_transport->stream, file_transport->color_normal);
    }
    else
    {
        file_transport_write_string(file_transport->stream, message_buffer_get_data(buf));
    }

    message_buffer_destroy(buf);
}
size_t file_transport_write_string(FILE* stream, string_t str)
{
    ASSERT(stream != NULL, 0);
    ASSERT(str != NULL, 0);

    fwrite(str, 1, strlen(str), stream);
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

int file_transport_setopt(file_transport_t *transport, transport_option_t option, unsigned long long int data)
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
    else if (TRANSPORT_OPT_DATETIME_FORMAT == option)
    {
        strncpy(transport->super.datetime_format, (string_t)data, TRANSPORT_DATE_TIME_FORMAT_MAX_SIZE);
        return 0;
    }
    return transport_setopt((transport_t*)transport, option, data);
}
