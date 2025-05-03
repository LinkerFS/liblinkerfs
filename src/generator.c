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

#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#include "log/log.h"
#include "liblinkerfs/generator.h"

#include "linkerfs/filesystem/data/header_info.h"
#include "linkerfs/filesystem/data/part_info.h"

typedef struct path_info_helper
{
    bool duplicate;
    int32_t offset;
} PATH_INFO_HELPER;

/**
 *
 * @param a a warp target
 * @param b another warp target
 * @return 0 if equal
 */
static int compare_path(const WARP_TARGET* a, const WARP_TARGET* b)
{
    // should we use strstr() for further optimization, or compare addresses directory for faster performance
    if (a->path_length != b->path_length)
        return -1;
    return memcmp(a->file_path, b->file_path, a->path_length);
}

static int32_t calculate_path_info_size(const WARP_CONFIG* warp_config, PATH_INFO_HELPER* path_helper_array)
{
    int32_t path_info_size = warp_config->warp_targets->path_length;
    for (uint16_t i = 1; i < warp_config->warp_count; ++i)
    {
        const WARP_TARGET* target = warp_config->warp_targets + i;
        for (uint16_t j = 0; j < i; ++j)
        {
            if (path_helper_array[j].duplicate)
                continue;
            const WARP_TARGET* target_previous = warp_config->warp_targets + j;
            if (compare_path(target, target_previous) == 0)
            {
                path_helper_array[i].offset = path_helper_array[j].offset;
                path_helper_array[i].duplicate = true;
                break;
            }
        }
        if (!path_helper_array[i].duplicate) {
            path_helper_array[i].offset = path_info_size;
            path_info_size += target->path_length;
        }
    }
    return path_info_size;
}

static void write_header(const WARP_CONFIG* warp_config, const int64_t size, unsigned char* buf)
{
    LINKERFS_HEADER header = {
        .part_info_begin_offset = header_length,
        .warp_size = size,
        .num_parts = warp_config->warp_count,
        .fmt_version.major = 0,
        .fmt_version.minor = 0,
        .reserved={0}
    };
    memcpy(header.magic, magic_number, sizeof(magic_number));
    memcpy(buf, &header, header_length);
}

static void write_part_info(const WARP_TARGET* target, LINKERFS_PART* part,
                            const PATH_INFO_HELPER* path_helper_array, const int32_t path_offset)
{
    part->path_length = target->path_length;
    part->path_offset = path_offset + path_helper_array->offset;
    part->data_begin_offset = target->offset_in_file;
    part->data_size = target->size_to_read;
    memset(part->reserved, 0, sizeof(part->reserved));
}

static void write_path_info(const WARP_TARGET* target, unsigned char* path_info_begin, const PATH_INFO_HELPER* path_helper)
{
    if (!path_helper->duplicate)
    {
        memcpy(path_info_begin + path_helper->offset, target->file_path, target->path_length);
    }
}

static int64_t write_part_info_and_path_info(const WARP_CONFIG* warp_config, unsigned char* part_info_begin,
                                             const PATH_INFO_HELPER* path_helper_array, const int32_t path_offset)
{
    int64_t total_size = 0;
    for (uint16_t i = 0; i < warp_config->warp_count; ++i)
    {
        LINKERFS_PART* part = (LINKERFS_PART*)part_info_begin + i;
        write_part_info(warp_config->warp_targets + i, part, path_helper_array + i, header_length + path_offset);
        write_path_info(warp_config->warp_targets + i, part_info_begin + path_offset, path_helper_array + i);
        total_size += part->data_size;
    }
    return total_size;
}

WARP_FILE generate_warp_file(const WARP_CONFIG* warp_config)
{
    WARP_FILE warp_file = {0};
    if (!warp_config || warp_config->warp_count == 0)
    {
        return warp_file;
    }
    const int32_t part_info_size = sizeof(LINKERFS_PART) * warp_config->warp_count;
    PATH_INFO_HELPER* path_helper = calloc(warp_config->warp_count, sizeof(PATH_INFO_HELPER));
    if (!path_helper)
    {
        LOG_OOM_MSG;
        return warp_file;
    }
    warp_file.length = header_length + part_info_size + calculate_path_info_size(warp_config, path_helper);
    warp_file.data = malloc(warp_file.length);
    if (!warp_file.data)
    {
        LOG_OOM_MSG;
        return warp_file;
    }
    const int64_t total_size = write_part_info_and_path_info(warp_config, warp_file.data + header_length,
                                                             path_helper, part_info_size);
    write_header(warp_config, total_size, warp_file.data);
    free(path_helper);
    return warp_file;
}

void release_warp_file(WARP_FILE* warp_file)
{
    if (warp_file)
    {
        free(warp_file->data);
        warp_file->data = NULL;
    }
}
