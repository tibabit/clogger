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

#include "message_buffer.h"

#include <stdlib.h>
#include <string.h>


#define MESSAGE_BUFFER_BLOCK_SIZE 64

typedef struct _message_buffer_t
{
    string_t data;
    size_t len;
    size_t capacity;
}message_buffer_t;

int message_buffer_resize(message_buffer_t* buffer, size_t new_size);

message_buffer_t * message_buffer_new(size_t capacity)
{
    if (capacity == 0)
    {
        capacity = MESSAGE_BUFFER_BLOCK_SIZE;
    }

    message_buffer_t * msg_buf = calloc(1, sizeof(message_buffer_t));
    ENSURE(msg_buf != NULL, NULL);

    message_buffer_resize(msg_buf, capacity);

    return msg_buf;
}
void message_buffer_destroy(message_buffer_t *buffer)
{
    ASSERT(buffer != NULL);

    FREE_IF_NOT_NULL(buffer->data);

    free(buffer);
}

int message_buffer_append(message_buffer_t *buffer, string_t data, size_t size)
{
    ASSERT(buffer != NULL, -1);
    ASSERT(data != NULL, -1);
    if (buffer->len + size >= buffer->capacity)
    {
        int res = message_buffer_resize(buffer, buffer->len * 2);

        ENSURE(res == 0, res);
    }

    memcpy(buffer->data + buffer->len, data, size);
    buffer->len += size;
    buffer->data[buffer->len] = '\0';

    return 0;
}
size_t message_buffer_get_length(message_buffer_t *buffer)
{
    ASSERT(buffer != NULL, 0);
    return buffer->len;
}
string_t message_buffer_get_data(message_buffer_t *buffer)
{
    ASSERT(buffer != NULL, NULL);

    return buffer->data;
}

int message_buffer_resize(message_buffer_t* buffer, size_t new_size)
{
    ASSERT(buffer != NULL, -1);

    buffer->data = realloc(buffer->data, new_size);

    ASSERT(buffer->data != NULL, -1);

    buffer->capacity = new_size;
}
