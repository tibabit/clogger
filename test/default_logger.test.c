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

void test_default_logger()
{

    clogger_emergd("Emergency type log %s", "arg 1");
    clogger_alertd("Alert type log");
    clogger_critd("Ciritcal type log");
    clogger_noticed("Notice type log");
    clogger_infod("Info type log %s", "arg 1");
    clogger_warnd("Warning type log");
    clogger_errord("Error type log");
    clogger_debugd("Debug type log");
}

void test_default_logger_change_severity()
{
    extern clogger *default_logger;
    transport_t* transport = clogger_get_transport(default_logger, "console");
    if (transport != NULL)
    {
        transport->setopt(transport, TRANSPORT_OPT_SEVERITY, SEVERITY_DEBUG);
    }
    clogger_emergd("Emergency type log %s", "arg 1");
    clogger_alertd("Alert type log");
    clogger_critd("Ciritcal type log");
    clogger_noticed("Notice type log");
    clogger_infod("Info type log %s", "arg 1");
    clogger_warnd("Warning type log");
    clogger_errord("Error type log");
    clogger_debugd("Debug type log");
}

int main()
{
    test_default_logger();
    test_default_logger_change_severity();
}
