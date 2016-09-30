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

#include "message_filter.h"

#include <stdlib.h>

#include "internals.h"

bool_t message_filter_filter(transport_t *transport, log_entry_t *entry);

message_filter_t * message_filter_new()
{
    message_filter_t* message_filter = calloc(1, sizeof(message_filter_t));
    ENSURE(message_filter != NULL, NULL);

    message_filter->filter = message_filter_filter;

    return message_filter;
}

void message_filter_destroy(message_filter_t *message_filter)
{
    ASSERT(message_filter != NULL);

    free(message_filter);
}

bool_t message_filter_filter(transport_t *transport, log_entry_t *entry)
{
    ASSERT(transport != NULL, FALSE);
    ASSERT(entry != NULL, FALSE);

    if (transport->severity >= entry->severity)
    {
        return TRUE;
    }
    return FALSE;
}