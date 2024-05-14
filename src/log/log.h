/*
 * liblinkerfs: a utils library for project linkerfs
 * Copyright (C) 2024  kaedeair <kaedeair@outlook.com>
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

#ifndef LIBLINKERFS_LOG_H
#define LIBLINKERFS_LOG_H

#include "macros.h"

#define DEBUG_MSG(...) \
do{                    \
        debug_output(__FILE_NAME__,__LINE__,__func__,__VA_ARGS__);               \
}while(0)

#define LOG_OOM_MSG DEBUG_MSG("Out of Memory!")

void debug_output(const char *src_file, int line_num, const char *func, const char *format,
                  ...) LIBLINKERFS_CHK_PRINTF(4, 5);

#endif //LIBLINKERFS_LOG_H
