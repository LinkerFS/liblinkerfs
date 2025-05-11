/*
 * liblinkerfs: a utils library for project linkerfs
 * Copyright (C) 2024-2025  kaedeair <kaedeair@outlook.com>
 *
 * This file is part of liblinkerfs.
 *
 * liblinkerfs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * liblinkerfs is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with liblinkerfs. If not, see <https://www.gnu.org/licenses/>.
 */

#include "log.h"

#include <stdarg.h>
#include <stdio.h>

#include "liblinkerfs/log/log_config.h"


static LIBLINKERFS_LOG_FUNC log_func = NULL;

void liblinkerfs_set_log_handler(LIBLINKERFS_LOG_FUNC func) {
    log_func = func;
}

void debug_output(const char *src_file, int line_num, const char *func, const char *format, ...) {
    char buffer[4096];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer) - 1, format, args);
    va_end(args);
    if (log_func) {
        log_func(src_file, line_num, func, buffer);
    } else {
        fprintf(stderr, "liblinkerfs: %s:%d func %s: %s\n", src_file, line_num, func, buffer);
    }
}
