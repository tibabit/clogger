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

#include "clogger.h"

void test_console_transport()
{
    clogger* logger = clogger_init();
    // add default transports
    console_transport_t * console_transport = console_transport_new();
    console_transport_setopt(console_transport, TRANSPORT_OPT_SEVERITY, SEVERITY_DEBUG);
    clogger_add_transport(logger, (transport_t *)console_transport);

    clogger_emerg(logger, "Emergency type log %s", "arg 1");
    clogger_alert(logger, "Alert type log");
    clogger_crit(logger, "Ciritcal type log");
    clogger_notice(logger, "Notice type log");
    clogger_info(logger, "Info type log %s", "arg 1");
    clogger_warn(logger, "Warning type log");
    clogger_error(logger, "Error type log");
    clogger_debug(logger, "Debug type log");

    clogger_destroy(logger);
}

int main()
{
    test_console_transport();
}
