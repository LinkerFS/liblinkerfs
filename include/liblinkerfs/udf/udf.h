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

/**
 * describe the position and length of data for a specific file in the UDF file system
 */
typedef struct udf_warp_target
{
    UDFFILE_INFO* file_info; //metadata and attributes of a specific file in the UDF file system
    off_t offset_in_file; //the position where the data in the file you want to read begins
    ssize_t size_to_read;
} UDF_WARP_TARGET;

typedef struct udf_warp_config
{
    UDF_WARP_TARGET* targets;
    const char* udf_file_path;  //udf file absolute full path
    uint32_t file_path_length;  //length of `udf_file_path`
    uint16_t target_count;
} UDF_WARP_CONFIG;

/**
 * convert udf warp config to warp configuration file
 * @param udf_warp_config udf warp config to convert
 * @return warp file content with length, should release with `release_warp_file` after using
 */
LIBLINKERFS_PUBLIC WARP_FILE udf_generate_warp_file(const UDF_WARP_CONFIG* udf_warp_config);

#ifdef  __cplusplus
}
#endif
#endif //LIBLINKERFS_UDF_H
