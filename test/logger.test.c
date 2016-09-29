#include "clogger.h"

int main()
{
    clogger* logger = clogger_init();

    logger->info(logger, "Info type log %s", "arg 1");
    logger->warn(logger, "Warning type log");
    logger->error(logger, "Error type log");
    logger->debug(logger, "Debug type log");

    clogger_destroy(logger);
}
