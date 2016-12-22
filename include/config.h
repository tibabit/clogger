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

#ifndef CONFIG_H

#define CONFIG_H

/** colors */
#define COLOR(ANSI_CODE)        ("\x1b[3"#ANSI_CODE"m")
#define COLOR_GREEN             COLOR(2)
#define COLOR_RED               COLOR(1)
#define COLOR_BLUE              COLOR(4)
#define COLOR_YELLOW            COLOR(3)
#define COLOR_CYAN              COLOR(6)
#define COLOR_WHITE             COLOR(7)

#define COLOR_EMERGENCY         COLOR_RED
#define COLOR_ALERT             COLOR_RED
#define COLOR_CRITICAL          COLOR_RED
#define COLOR_ERROR             COLOR_RED
#define COLOR_WARNING           COLOR_YELLOW
#define COLOR_NOTICE            COLOR_BLUE
#define COLOR_INFO              COLOR_GREEN
#define COLOR_DEBUG             COLOR_CYAN
#define COLOR_NORMAL            ("\x1b[0m")

#define DEFAULT_LOG_SEVERITY            SEVERITY_INFO
#define DEFAULT_LOG_FORMAT_FILE         "%y - %t: %m%n"
#define DEFAULT_LOG_FORMAT_CONSOLE      "%t: %m%n"
#define DEFAULT_DATETIME_FORMAT         "%FT%TZ"


#define NEWLINE     "\n"

#endif /* end of include guard: CONFIG_H */

