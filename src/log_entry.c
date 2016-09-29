#include "log_entry.h"

#include <stdlib.h>
#include <string.h>

#include "internals.h"


log_entry_t* log_entry_new()
{
    log_entry_t* entry = malloc(sizeof(log_entry_t));

    ENSURE(entry != NULL, NULL);

    return entry;
}

void log_entry_destroy(log_entry_t * entry)
{
    ASSERT(entry != NULL);

    /** free up all memories */
}
