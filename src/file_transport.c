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

#include <stdlib.h>

#include "internals.h"
#include "config.h"

void file_transport_write(transport_t *transport, log_entry_t *entry);
void file_transport_destory(transport_t *transport);

file_transport_t * file_transport_new()
{
    file_transport_t *transport = calloc(1, sizeof(file_transport_t));

    ENSURE(transport != NULL, NULL);

    transport->write = file_transport_write;
    transport->destroy = file_transport_destory;
    transport->severity = DEFAULT_LOG_SEVERITY;

    return transport;
}

void file_transport_write(transport_t *transport, log_entry_t *entry)
{
    ASSERT(transport != NULL);
    ASSERT(entry != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    vfprintf(file_transport->stream, entry->msg_frmt, *(entry->msg_args));
    fprintf(file_transport->stream, "\n");
}

void file_transport_destory(transport_t *transport)
{
    ASSERT(transport != NULL);

    file_transport_t *file_transport = (file_transport_t *)transport;

    if (file_transport->stream != NULL)
    {
        fclose(file_transport->stream);
    }

    free(transport);

}