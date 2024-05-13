/*
 * liblinkerfs: a utils library for linkerfs
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

#ifndef LIBLINKERFS_LOG_CONFIG_H
#define LIBLINKERFS_LOG_CONFIG_H

typedef void (*LIBLINKERFS_LOG_FUNC)(const char *file, int line, const char *func, const char *msg);

void liblinkerfs_set_log_handler(LIBLINKERFS_LOG_FUNC func);

#endif //LIBLINKERFS_LOG_CONFIG_H
