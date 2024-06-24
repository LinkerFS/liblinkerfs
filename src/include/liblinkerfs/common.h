/*
 * liblinkerfs: a utils library for project linkerfs
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

#ifndef LIBLINKERFS_COMMON_H
#define LIBLINKERFS_COMMON_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "liblinkerfs_export.h"
#include <stdint.h>

/**
 * feature mask
 */
typedef enum feature {
    FEATURE_BASE = 0
} FEATURE;

/**
 * get the feature of library
 * @return feature mask
 */
LIBLINKERFS_PUBLIC uint64_t feature();

#ifdef __cplusplus
}
#endif
#endif //LIBLINKERFS_COMMON_H
