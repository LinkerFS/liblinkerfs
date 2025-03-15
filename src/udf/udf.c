/*
 * liblinkerfs: a utils library for linkerfs
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

#include <stdlib.h>
#include <memory.h>

#include "udfread/udfread.h"
#include "linkerfs/filesystem/data/header_info.h"
#include "linkerfs/filesystem/data/part_info.h"
#include "liblinkerfs/udf/udf.h"
#include "../log/log.h"

UDF_WARP_RESULT
udf_try_generate_warp_file(const char *udf_file_path, const char *file_path_in_udf,
                           const off_t begin, const size_t size_to_read) {
    udfread *udf;
    UDFFILE *udf_file;
    UDFFILE_INFO *file_info;
    UDF_WARP_RESULT result;

    result.data = NULL;
    udf = udfread_init();
    if (!udf) {
        return result;
    }
    udfread_open(udf, udf_file_path);
    udf_file = udfread_file_open(udf, file_path_in_udf);
    if (!udf_file) {
        udfread_close(udf);
        return result;
    }


    file_info = udfread_get_file_info(udf_file);
    if (begin >= file_info->length) {
        DEBUG_MSG("%s in %s offset %ld is out of range %lu",
                  file_path_in_udf, udf_file_path, begin, file_info->length);
        goto release_source;
    }

    if (file_info->content_inline) {
        const uint32_t data_length =
                file_info->u.data.information_length - begin > size_to_read
                ? size_to_read
                : file_info->u.data.information_length - begin;
        result.type = UDF_RAW_DATA;
        result.data = malloc(data_length);
        result.data_size = data_length;
        memcpy(result.data, file_info->u.data.content, data_length);
    } else {
        result.type = UDF_WARP_DATA;
        result.data = udf_generate_warp_file(file_info, udf_file_path, begin, size_to_read, &result.data_size);
    }
    release_source:
    free(file_info);
    udfread_file_close(udf_file);
    udfread_close(udf);
    return result;
}

void udf_realse_result(UDF_WARP_RESULT **result) {
    if (result)
    {
        free((*result)->data);
        (*result)->data = NULL;
    }
}

unsigned char *
udf_generate_warp_file(const UDFFILE_INFO *file_info, const char *udf_file_path, const off_t begin,
                       const size_t size_to_read, uint32_t *data_length) {
    const uint32_t udf_file_path_length = strlen(udf_file_path);
    const uint32_t parts_info_length = sizeof(struct part_info) * file_info->u.parts.num_parts;
    const uint32_t warp_file_length = header_length + parts_info_length + udf_file_path_length;

    LINKERFS_PART *part;
    LINKERFS_HEADER *header;
    header = malloc(warp_file_length);
    if (!header) {
        LOG_OOM_MSG;
        return NULL;
    }
    header->num_parts = file_info->u.parts.num_parts;
    header->part_info_begin_offset = header_length;
    header->warp_size = file_info->length;
    header->num_parts = file_info->u.parts.num_parts;
    header->fmt_version.major = 0;
    header->fmt_version.minor = 0;
    header->unused = 0;
    memcpy(header->magic, magic_number, sizeof(magic_number));
    part = (LINKERFS_PART *) ((char *) header + header_length);
    for (uint32_t i = 0; i < file_info->u.parts.num_parts; ++part, ++i) {
        part->data_begin_offset = (file_info->u.parts.udf_part_info + i)->offset;
        part->data_size = (file_info->u.parts.udf_part_info + i)->length;
        part->path_length = udf_file_path_length;
        part->path_offset = header_length + parts_info_length;
        part->unused = 0;
    }
    memcpy(part, udf_file_path, udf_file_path_length);
    *data_length = warp_file_length;
    return (unsigned char *) header;
}