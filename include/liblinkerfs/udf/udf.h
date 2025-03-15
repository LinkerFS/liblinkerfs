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
#include "liblinkerfs/data/warp.h"

typedef enum udf_warp_type {
    UDF_RAW_DATA,
    UDF_WARP_DATA
} UDF_WARP_TYPE;

typedef struct udf_warp_result {
    unsigned char *data;
    uint32_t data_size;
    UDF_WARP_TYPE type;
} UDF_WARP_RESULT;

LIBLINKERFS_PUBLIC
UDF_WARP_RESULT udf_try_generate_warp_file(const char *udf_file_path, const char *file_path_in_udf, const off_t begin,
                                           const size_t size_to_read);

LIBLINKERFS_PUBLIC void udf_realse_result(UDF_WARP_RESULT **result);

LIBLINKERFS_PRIVATE
unsigned char *
udf_generate_warp_file(const UDFFILE_INFO *file_info, const char *udf_file_path, const off_t begin, const size_t size_to_read, uint32_t *data_length);


#ifdef  __cplusplus
}
#endif
#endif //LIBLINKERFS_UDF_H
