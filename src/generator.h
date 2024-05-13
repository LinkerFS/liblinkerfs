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

#ifndef LIBLINKERFS_GENERATOR_H
#define LIBLINKERFS_GENERATOR_H

#include "data/warp.h"


size_t calculate_buf_size(const WARP_CONFIG *warp_config);

const unsigned char *generate_warp_file(const WARP_CONFIG *warp_config, size_t *warp_file_size);

#endif //LIBLINKERFS_GENERATOR_H