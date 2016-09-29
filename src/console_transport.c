#include "console_transport.h"

#include <stdlib.h>

#include "internals.h"

console_transport_t * console_transport_new()
{
    console_transport_t *transport = file_transport_new();

    ENSURE(transport != NULL, NULL);

    transport->stream = stdout;

    return transport;
}
