#include "clogger.h"

int main()
{
    clogger_init();

    logger.info("Info type log %s", "arg 1");
    logger.warn("Warning type log");
    logger.error("Error type log");
    logger.debug("Debug type log");

}
