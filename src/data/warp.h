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

#ifndef LIBLINKERFS_WARP_H
#define LIBLINKERFS_WARP_H

#include <stdint.h>

typedef struct wrap_target {
    int64_t size_to_read;
    int64_t offset_in_file;
    int32_t path_length;
    char *file_path;
} WARP_TARGET;

typedef struct wrap_config {
    WARP_TARGET *warp_targets;
    int warp_count;
} WARP_CONFIG;
#endif //LIBLINKERFS_WARP_H
