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

#ifndef LIBLINKERFS_UDF_H
#define LIBLINKERFS_UDF_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "udfread/udfread.h"
#include "liblinkerfs/liblinkerfs_export.h"
#include "liblinkerfs/generator.h"


typedef struct udf_warp_target
{
    UDFFILE_INFO* file_info;
    off_t offset_in_file;
    ssize_t size_to_read;
} UDF_WARP_TARGET;

typedef struct udf_warp_config
{
    UDF_WARP_TARGET* targets;
    const char* udf_file_path;
    uint32_t file_path_length;
    uint16_t target_count;
} UDF_WARP_CONFIG;

LIBLINKERFS_PUBLIC WARP_FILE udf_generate_warp_file(const UDF_WARP_CONFIG* udf_warp_config);

#ifdef  __cplusplus
}
#endif
#endif //LIBLINKERFS_UDF_H
