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

#ifndef LIBLINKERFS_LOG_CONFIG_H
#define LIBLINKERFS_LOG_CONFIG_H

#include "liblinkerfs/liblinkerfs_export.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*LIBLINKERFS_LOG_FUNC)(const char *file, int line, const char *func, const char *msg);

/**
 * set custom logger and disable stdout/stderr
 * @param func custom log function, if null, do nothing
 */
LIBLINKERFS_PUBLIC void liblinkerfs_set_log_handler(LIBLINKERFS_LOG_FUNC func);

#ifdef __cplusplus
}
#endif
#endif  //LIBLINKERFS_LOG_CONFIG_H
