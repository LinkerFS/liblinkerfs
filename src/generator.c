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

#include <string.h>
#include <malloc.h>
#include "generator.h"
#include "linkferfs/header_info.h"
#include "linkferfs/part_info.h"

size_t calculate_buf_size(const WARP_CONFIG *warp_config) {
    size_t wrap_config_size = 0;
    const uint32_t warp_count = warp_config->warp_count;

    wrap_config_size += header_length;
    wrap_config_size += part_info_length * warp_count;
    for (uint32_t i = 0; i < warp_count; ++i) {
        wrap_config_size += warp_config->warp_targets->path_length;
    }
    return wrap_config_size;
}

void write_header(const WARP_CONFIG *warp_config, const int64_t size, unsigned char *buf) {
    LINKERFS_HEADER header = {
            .part_info_begin_offset=header_length,
            .warp_size=size,
            .num_parts=warp_config->warp_count,
            .fmt_version.major=0,
            .fmt_version.minor=0,
            .unused=0
    };

    memcpy(header.magic, magic_number, sizeof(magic_number));
    memcpy(buf, &header, header_length);
}

/**
 *
 * @param warp_config
 * @param buf parts info begin address in a buffer
 * @return
 */
int64_t write_parts_and_path(const WARP_CONFIG *warp_config, unsigned char *buf) {
    LINKERFS_PART *part_cur;
    WARP_TARGET *warp_target;
    int path_offset;
    int64_t total_size = 0;

    warp_target = warp_config->warp_targets;
    part_cur = (LINKERFS_PART *) buf;
    path_offset = part_info_length * warp_config->warp_count;
    for (uint32_t i = 0; i < warp_config->warp_count; ++i, ++part_cur, ++warp_target) {
        LINKERFS_PART part = {
                .data_size          =   warp_target->size_to_read,
                .data_begin_offset  =   warp_target->offset_in_file,
                .path_offset        =   path_offset + header_length,
                .path_length        =   warp_target->path_length
        };
        total_size += part.data_size;
        memcpy(part_cur, &part, sizeof(LINKERFS_PART));
        memcpy(buf + path_offset, warp_target->file_path, warp_target->path_length);
        path_offset += warp_target->path_length;
    }
    return total_size;
}


/**
 *
 * @param warp_config
 * @param warp_file_size pass the size of the returned content
 * @return warp configuration file content, need to free
 */
const unsigned char *generate_warp_file(const WARP_CONFIG *warp_config, size_t *warp_file_size) {
    unsigned char *buf;
    int64_t warp_size;
    const size_t config_size = calculate_buf_size(warp_config);

    *warp_file_size = config_size;
    buf = (unsigned char *) malloc(config_size);
    warp_size = write_parts_and_path(warp_config, buf + header_length);
    write_header(warp_config, warp_size, buf);

    return buf;
}
