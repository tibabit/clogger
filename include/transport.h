#ifndef TRANSPORT_H

#define TRANSPORT_H

#include "log_entry.h"

typedef struct _transport transport_t;

typedef void (*msg_writer_fn)(transport_t *transport, log_entry_t *entry);
typedef void (*destroy_transport_fn)(transport_t *transport);

typedef struct _transport
{
    msg_writer_fn write;
    destroy_transport_fn destroy;
}transport_t;

#endif /* end of include guard: TRANSPORT_H */
