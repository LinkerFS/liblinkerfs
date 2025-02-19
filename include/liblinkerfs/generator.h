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
#ifdef __cplusplus
extern "C"
{
#endif

#include "liblinkerfs_export.h"
#include "data/warp.h"

/**
 * get the size of warp configuration file
 * @param warp_config config data
 * @return size of warp configuration file
 */
LIBLINKERFS_PUBLIC size_t calculate_buf_size(const WARP_CONFIG *warp_config);

/**
 * get the data of warp configuration file
 * @param warp_config config data
 * @param warp_file_size the size of warp configuration file
 * @return the pointer of data, should be free after using
 */
LIBLINKERFS_PUBLIC const unsigned char *generate_warp_file(const WARP_CONFIG *warp_config, size_t *warp_file_size);

#ifdef __cplusplus
}
#endif
#endif //LIBLINKERFS_GENERATOR_H