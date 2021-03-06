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

#include "transport.h"

#include <string.h>
#include <stdlib.h>

#include "internals.h"

transport_t* transport_new()
{
    transport_t* transport = CALLOC(transport_t);

    ENSURE(transport != NULL, NULL);

    transport_init(transport);

    return transport;
}

void transport_init(transport_t* transport)
{
    ASSERT(transport != NULL);

    transport->setopt = transport_setopt;

}

void transport_release(transport_t* transport)
{
    ASSERT(transport != NULL);
    FREE_IF_NOT_NULL(transport->name);
}

void transport_destroy(transport_t* transport)
{
    ASSERT(transport != NULL);

    transport_release(transport);

    FREE_IF_NOT_NULL(transport);
}

int transport_setopt(transport_t *transport, transport_option_t option, transport_opt_data_t data)
{
    if (TRANSPORT_OPT_NAME == option)
    {
        FREE_AND_COPY(transport->name, (string_t)data);
        return 0;
    }
    else if (TRANSPORT_OPT_SEVERITY == option)
    {
        transport->severity = (log_severity_t)data;
        return 0;
    }
    else if (TRANSPORT_OPT_DATETIME_FORMAT == option)
    {
        strncpy(transport->datetime_format, (string_t)data, TRANSPORT_DATE_TIME_FORMAT_MAX_SIZE);
        return 0;
    }

    return -1;
}
