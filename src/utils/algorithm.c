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

#include "liblinkerfs/utils/algorithm.h"

#include <memory.h>

void swap_item(void *a, void *b, size_t size) {
    if (a == b)
        return;
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void insert_sort(void *base, size_t array_length, uint32_t element_size, int (*compare)(const void *, const void *)) {
    char *array;
    char *current_ptr;
    char *compare_ptr;

    if (array_length == 1)
        return;
    array = (char *) base;
    compare_ptr = array;
    current_ptr = array + element_size;
    while (current_ptr < array + array_length * element_size) {
        while (current_ptr < array + array_length * element_size
               && compare(current_ptr, compare_ptr + element_size) > 0)
            current_ptr += element_size;
        compare_ptr = current_ptr - element_size;
        while (compare(compare_ptr, compare_ptr + element_size) > 0) {
            swap_item(compare_ptr, compare_ptr + element_size, sizeof(intptr_t));
            if (compare_ptr > array)
                compare_ptr -= element_size;
        }
        current_ptr += element_size;
        compare_ptr = current_ptr - element_size;
    }
}

static size_t bfprt_partition(void *base, size_t pivot_idx, size_t array_length, uint32_t element_size,
                              int (*compare)(const void *, const void *)) {
    char *array;
    char *head;
    char *tail;

    array = (char *) base;
    swap_item(array, array + element_size * pivot_idx, sizeof(intptr_t));
    head = array + element_size;
    tail = array + element_size * (array_length - 1);
    while (head < tail) {
        while (compare(tail, array) > 0 && head < tail)
            tail -= element_size;
        while (compare(array, head) > 0 && head < tail)
            head += element_size;
        swap_item(head, tail, sizeof(intptr_t));
        if (compare(head, array) == 0) {
            swap_item(head, head + (((tail - head) / element_size) >> 1) * element_size, sizeof(intptr_t));
            head += element_size;
        }
        if (compare(tail, array) == 0) {
            swap_item(tail, head + (((tail - head) / element_size) >> 1) * element_size, sizeof(intptr_t));
            tail -= element_size;
        }
    }
    if (compare(head, array) > 0)
        swap_item(array, tail - element_size, sizeof(intptr_t));
    else
        swap_item(array, head, sizeof(intptr_t));
    return (head - array) / element_size;
}

static size_t bfprt_get_median_of_median(void *base, size_t size, uint32_t element_size,
                                         int (*compare)(const void *, const void *)) {
    char *array;
    const size_t num_group = size / 5;

    array = base;
    for (size_t i = 0; i < num_group; ++i) {
        insert_sort(array + i * element_size * 5, 5, element_size, compare);
        swap_item(array + i * element_size, array + i * element_size * 5 + element_size * 2, sizeof(intptr_t));
    }
    return bfprt(array, (num_group >> 1) > 0 ? (num_group >> 1) : 1, num_group, element_size, compare);
}

size_t bfprt(void *array, size_t top_k, size_t array_length, uint32_t element_size,
             int (*compare)(const void *, const void *)) {

    size_t pivot_idx;
    size_t num_order;
    size_t sub_idx;

    if (array_length <= 5) {
        insert_sort(array, array_length, element_size, compare);
        return array_length - top_k;
    }
    pivot_idx = bfprt_get_median_of_median(array, array_length, element_size, compare);
    pivot_idx = bfprt_partition(array, pivot_idx, array_length, element_size, compare);
    num_order = array_length - pivot_idx;
    if (top_k == num_order)
        return pivot_idx;
    else if (top_k > num_order)
        return bfprt(array, top_k - num_order, array_length - num_order, element_size, compare);
    else {
        sub_idx = bfprt(array + (pivot_idx + 1) * element_size, top_k, num_order - 1, element_size, compare);
        return pivot_idx + 1 + sub_idx;
    }
}
