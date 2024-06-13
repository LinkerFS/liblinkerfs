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

#ifndef LIBLINKERFS_ALGORITHM_H
#define LIBLINKERFS_ALGORITHM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include "liblinkerfs_export.h"

LIBLINKERFS_PUBLIC void swap_item(void *a, void *b, size_t size);

LIBLINKERFS_PUBLIC size_t bfprt(void *base, size_t top_k, size_t array_length, uint32_t element_size,
                                int (*ptr_func_compare)(const void *, const void *));

LIBLINKERFS_PUBLIC void insert_sort(void *base, size_t array_length, uint32_t element_size,
                                    int (*ptr_func_compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif
#endif //LIBLINKERFS_ALGORITHM_H
