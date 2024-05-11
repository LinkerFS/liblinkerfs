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

#ifndef LINKERFS_HEADER_INFO_H
#define LINKERFS_HEADER_INFO_H


#include <stdint.h>

/*
 *  magic_number: hex "0xD1 0xFE LinkerFS 0xB7 0xE3"
 */
static const unsigned char magic_number[12] = {0xD1, 0xFE, 0x4c, 0x69, 0x6e, 0x6b, 0x65, 0x72, 0x46, 0x53, 0xB7, 0xE3};

typedef struct file_format_version {
    uint8_t major;
    uint8_t minor;
} LINKERFS_WARP_VERSION;

typedef struct header_info {
    uint8_t magic[12];
    int32_t part_info_begin_offset;
    int64_t warp_size;
    uint16_t num_parts;
    LINKERFS_WARP_VERSION fmt_version;
    uint32_t unused;
} LINKERFS_HEADER;

static const unsigned char header_length = sizeof(LINKERFS_HEADER);

#endif //LINKERFS_HEADER_INFO_H
