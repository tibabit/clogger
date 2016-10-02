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

#define DATE_TIME_STR_SIZE 32

#define NULL_TEXT           "(null)"
#define IF_NULL(str, alt)   (((str) == NULL) ? (alt) : (str))

string_t log_formatter_format(const string_t frmt, log_entry_t* entry)
{
    ASSERT(frmt != NULL, NULL);
    ASSERT(entry != NULL, NULL);

    // TODO handle timestamp
    size_t expected_log_length = strlen(frmt) +
        strlen(IF_NULL(entry->message, NULL_TEXT)) +
        strlen(IF_NULL(entry->catagory, NULL_TEXT)) +
        strlen(IF_NULL(entry->title, NULL_TEXT));

    string_t formatted_log = calloc(1, expected_log_length);
    ENSURE(formatted_log != NULL, NULL);

    string_t src = frmt;
    string_t dst = formatted_log;
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
                    case FORMAT_TITLE:
                        len = sprintf(dst, "%s", IF_NULL(entry->title, NULL_TEXT));
                        break;
                    case FORMAT_CATAGORY:
                        len = sprintf(dst, "%s", IF_NULL(entry->catagory, NULL_TEXT));
                        break;
                    case FORMAT_MESSAGE:
                        len = sprintf(dst, "%s", IF_NULL(entry->message, NULL_TEXT));
                        break;
                    default:
                        len = 0;
                        break;
                }
                dst += len;
                break;
            default:
                *dst = *src;
                dst++;
        }
        src++;
    }

    return formatted_log;
}
