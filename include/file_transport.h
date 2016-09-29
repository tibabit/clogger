#ifndef FILE_TRANSPORT_H

#define FILE_TRANSPORT_H

#include <stdio.h>

#include "transport.h"

typedef struct _file_transport
{
    msg_writer_fn write;
    destroy_transport_fn destroy;
    FILE *stream;
}file_transport_t;

file_transport_t * file_transport_new();

#endif /* end of include guard: FILE_TRANSPORT_H */
