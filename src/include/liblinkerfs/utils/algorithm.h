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

/**
 * function to compare element, return 0 if equal, positive number if first element greater, and negative otherwise
 */
typedef int (*COMPARE_FUNC)(const void *, const void *);

/**
 * swap item
 * @param a pointer of item a
 * @param b pointer of item b
 * @param size size of item in memory
 */
LIBLINKERFS_PUBLIC void swap_item(void *a, void *b, size_t size);

/**
 * get the index of the k-th largest element in a sequential array
 * @param base pointer of the array begin
 * @param top_k rank of largest element
 * @param array_length length of the array
 * @param element_size size of element in memory
 * @param compare custom function to compare element
 * @return index of k-th largest element
 */
LIBLINKERFS_PUBLIC size_t bfprt(void *base, size_t top_k, size_t array_length, uint32_t element_size,
                                COMPARE_FUNC compare);

/**
 * insert sort for a sequential array
 * @param base pointer of the array begin
 * @param array_length length of the array
 * @param element_size size of element in memory
 * @param compare custom function to compare element
 */
LIBLINKERFS_PUBLIC void insert_sort(void *base, size_t array_length, uint32_t element_size,
                                    COMPARE_FUNC compare);

#ifdef __cplusplus
}
#endif
#endif //LIBLINKERFS_ALGORITHM_H
