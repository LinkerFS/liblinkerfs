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

#ifndef LIBLINKERFS_GENERATOR_H
#define LIBLINKERFS_GENERATOR_H

#include <stddef.h>

#include "data/warp.h"
#include "liblinkerfs_export.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * data and length of warp configuration file
 */
typedef struct warp_file {
    size_t length;  //number of valid bytes in 'data'
    unsigned char *data;
} WARP_FILE;

/**
 * convert warp config to warp configuration file
 * @param warp_config warp config to convert
 * @return warp file content with length, should release with `release_warp_file` after using
 */
LIBLINKERFS_PUBLIC WARP_FILE generate_warp_file(const WARP_CONFIG *warp_config);

/**
 * release memory and set data to NULL for WARP_FILE
 * @param warp_file WARP_FILE to release
 */
LIBLINKERFS_PUBLIC void release_warp_file(WARP_FILE *warp_file);


#ifdef __cplusplus
}
#endif
#endif  //LIBLINKERFS_GENERATOR_H
