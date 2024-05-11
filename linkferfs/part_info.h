/*
 * LinkerFS: a data remapping filesystem
 * Copyright (C) 2024  kaedeair <kaedeair@outlook.com>
 *
 * This file is part of LinkerFS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LinkerFS. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LINKERFS_PART_INFO_H
#define LINKERFS_PART_INFO_H

#include <stdint.h>

typedef struct part_info {
    int64_t data_size;
    int64_t data_begin_offset;  //data begin offset in destination file
    int32_t path_offset;    //offset in this warp configuration file
    uint16_t path_length;
    uint16_t unused;
} LINKERFS_PART;

static const unsigned char part_info_length = sizeof(LINKERFS_PART);

#endif //LINKERFS_PART_INFO_H
