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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "log_formatter.h"
#include "internals.h"
#include "config.h"
#include "file_transport.h"
#include "clogger.h"

#define DATE_TIME_STR_SIZE 64

#define NULL_TEXT           "(null)"
#define IF_NULL(str, alt)   (((str) == NULL) ? (alt) : (str))

message_buffer_t* log_formatter_format(transport_t* transport, log_entry_t* entry)
{
    ASSERT(transport != NULL, NULL);
    ASSERT(entry != NULL, NULL);

    file_transport_t* file_transport = (file_transport_t*) transport;

    message_buffer_t* buf = message_buffer_new(0);

    ENSURE(buf != NULL, NULL);

    string_t src = file_transport->log_format;
    size_t len = 0;

    while (*src != '\0')
    {
        switch(*src)
        {
            case '%':
                src++;
                if (*src == '\0')
                {
                    break;
                }
                switch(*src)
                {
                    case FORMAT_TIME:
                        {
                            char datetime[DATE_TIME_STR_SIZE] = {0};
                            len = strftime(datetime,
                                    DATE_TIME_STR_SIZE,
                                    transport->datetime_format,
                                    gmtime(&entry->timestamp));
                            message_buffer_append(buf,
                                    datetime,
                                    len);
                        }
                        break;
                    case FORMAT_TITLE:
                        message_buffer_append(buf,
                                IF_NULL(entry->title, NULL_TEXT),
                                strlen(IF_NULL(entry->title, NULL_TEXT)));
                        break;
                    case FORMAT_CATAGORY:
                        message_buffer_append(buf,
                                IF_NULL(transport->logger->catagory, NULL_TEXT),
                                strlen(IF_NULL(transport->logger->catagory, NULL_TEXT)));
                        break;
                    case FORMAT_MESSAGE:
                        message_buffer_append(buf,
                                IF_NULL(entry->message, NULL_TEXT),
                                strlen(IF_NULL(entry->message, NULL_TEXT)));
                        break;
                    case FORMAT_NEWLINE:
                        message_buffer_append(buf,
                                NEWLINE,
                                strlen(NEWLINE));
                        break;
                    default:
                        break;
                }
                break;
            default:
                message_buffer_append(buf, src, 1);
        }
        src++;
    }

    return buf;
}
