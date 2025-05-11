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

#ifndef LIBLINKERFS_WARP_H
#define LIBLINKERFS_WARP_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * part info in warp configuration file
 */
typedef struct warp_target {
    int64_t size_to_read;
    int64_t offset_in_file;
    uint16_t path_length;
    const char *file_path;
} WARP_TARGET;

/**
 * base info of warp configuration file
 */
typedef struct warp_config {
    WARP_TARGET *warp_targets;
    uint16_t warp_count;
} WARP_CONFIG;

#ifdef __cplusplus
}
#endif
#endif  //LIBLINKERFS_WARP_H
