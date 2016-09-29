#include "file_transport.h"

#include <stdlib.h>

#include "internals.h"

void file_transport_write(transport_t *transport, log_entry_t *entry);
void file_transport_destory(transport_t *transport);

file_transport_t * file_transport_new()
{
    file_transport_t *transport = calloc(1, sizeof(file_transport_t));

    ENSURE(transport != NULL, NULL);

    transport->write = file_transport_write;
    transport->destroy = file_transport_destory;

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
}
