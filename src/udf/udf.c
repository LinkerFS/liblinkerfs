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

#include "udfread/udfread.h"
#include "linkerfs/filesystem/data/header_info.h"
#include "liblinkerfs/udf/udf.h"
#include "../log/log.h"

typedef struct udf_warp_target_helper
{
    struct content_parts
    {
        int64_t data_begin_relative_offset;
        int64_t data_end_relative_offset;
        uint32_t data_begin_file_info_index;
        uint32_t data_end_file_info_index;
    } content_parts;

    int64_t data_length;
    uint16_t num_targets;
} UDF_WARP_TARGET_HELPER;

struct udf_file_info_handler
{
    void (*num_warp_targets)(const UDF_WARP_TARGET* udf_warp_target, UDF_WARP_TARGET_HELPER* warp_target_helper);
    void (*convert_warp_target)(WARP_TARGET* warp_target, const UDF_WARP_TARGET* udf_warp_target,
                                const UDF_WARP_TARGET_HELPER* warp_target_helper,
                                const UDF_WARP_CONFIG* udf_warp_config);
};

static void content_inline_num_warp_targets(const UDF_WARP_TARGET* udf_warp_target,
                                            UDF_WARP_TARGET_HELPER* warp_target_helper)
{
    const ssize_t left_size = udf_warp_target->file_info->length - udf_warp_target->offset_in_file -
        udf_warp_target->size_to_read;
    if (left_size <= 0)
    {
        warp_target_helper->num_targets = 0;
        return;
    }

    warp_target_helper->data_length = udf_warp_target->size_to_read > left_size
                                          ? left_size
                                          : udf_warp_target->size_to_read;
    warp_target_helper->num_targets = 1;
}

static void content_parts_num_warp_targets(const UDF_WARP_TARGET* udf_warp_target,
                                           UDF_WARP_TARGET_HELPER* warp_target_helper)
{
    const ssize_t left_size = udf_warp_target->file_info->length - udf_warp_target->offset_in_file;
    if (left_size <= 0)
    {
        warp_target_helper->num_targets = 0;
        return;
    }
    //size of skipped data before find the beginning data
    ssize_t read_size = 0;
    const struct udf_part_info* part = udf_warp_target->file_info->u.parts.udf_part_info;
    int i = 0;
    while (i < udf_warp_target->file_info->u.parts.num_parts)
    {
        read_size += part->length;
        if (read_size > udf_warp_target->offset_in_file)
            break;
        ++i;
        ++part;
    }
    //size of the target data has been read
    read_size -= udf_warp_target->offset_in_file;
    warp_target_helper->content_parts.data_begin_file_info_index = i;
    warp_target_helper->content_parts.data_begin_relative_offset = part->length - read_size;

    while (read_size < udf_warp_target->size_to_read && i < udf_warp_target->file_info->u.parts.num_parts)
    {
        ++i;
        ++part;
        read_size += part->length;
    }
    warp_target_helper->content_parts.data_end_file_info_index = i;
    warp_target_helper->content_parts.data_end_relative_offset = part->length -
        (read_size - udf_warp_target->size_to_read);

    if (warp_target_helper->content_parts.data_end_relative_offset == 0)
    {
        warp_target_helper->content_parts.data_end_file_info_index = i - 1;
        warp_target_helper->content_parts.data_end_relative_offset = (part - 1)->length;
    }
    warp_target_helper->data_length = read_size;
    warp_target_helper->num_targets = warp_target_helper->content_parts.data_end_file_info_index -
        warp_target_helper->content_parts.data_begin_file_info_index + 1;
}

static void content_inline_warp_convert(WARP_TARGET* warp_target, const UDF_WARP_TARGET* udf_warp_target,
                                        const UDF_WARP_TARGET_HELPER* warp_target_helper,
                                        const UDF_WARP_CONFIG* udf_warp_config)
{
    warp_target->offset_in_file = udf_warp_target->file_info->u.data.offset + udf_warp_target->offset_in_file;
    warp_target->size_to_read = warp_target_helper->data_length;
    warp_target->path_length = udf_warp_config->file_path_length;
    warp_target->file_path = udf_warp_config->udf_file_path;
}

static void content_parts_warp_convert(WARP_TARGET* warp_target, const UDF_WARP_TARGET* udf_warp_target,
                                       const UDF_WARP_TARGET_HELPER* warp_target_helper,
                                       const UDF_WARP_CONFIG* udf_warp_config)
{
    const uint32_t begin_index = warp_target_helper->content_parts.data_begin_file_info_index;
    const uint32_t end_index = warp_target_helper->content_parts.data_end_file_info_index;
    for (uint32_t i = begin_index; i < udf_warp_target->file_info->u.parts.num_parts; ++i)
    {
        const struct udf_part_info* part = udf_warp_target->file_info->u.parts.udf_part_info + i;

        warp_target->path_length = udf_warp_config->file_path_length;
        warp_target->file_path = udf_warp_config->udf_file_path;
        if (i == begin_index)
        {
            warp_target->offset_in_file = warp_target_helper->content_parts.data_begin_relative_offset + part->offset;
            warp_target->size_to_read = part->length - warp_target_helper->content_parts.data_begin_relative_offset;
        }
        else if (i == end_index)
        {
            warp_target->offset_in_file = part->offset;
            warp_target->size_to_read = warp_target_helper->content_parts.data_end_relative_offset;
            break;
        }
        warp_target->offset_in_file = part->offset;
        warp_target->size_to_read = part->length;
        ++warp_target;
    }
}

static const struct udf_file_info_handler content_inline_handler = {
    .num_warp_targets = content_inline_num_warp_targets,
    .convert_warp_target = content_inline_warp_convert
};

static const struct udf_file_info_handler content_parts_handler = {
    .num_warp_targets = content_parts_num_warp_targets,
    .convert_warp_target = content_parts_warp_convert
};

static size_t calculate_warp_config_count(const UDF_WARP_CONFIG* udf_warp_config,
                                          UDF_WARP_TARGET_HELPER* warp_target_helper)
{
    size_t size = 0;
    if (!udf_warp_config->targets)
    {
        DEBUG_MSG("udf_warp_config->targets is NULL");
        return 0;
    }
    for (uint16_t i = 0; i < udf_warp_config->target_count; ++i)
    {
        const UDF_WARP_TARGET* target = udf_warp_config->targets + i;
        if (target->size_to_read == 0)
        {
            DEBUG_MSG("Skip a target index %d in %s for size_to_read is 0", i, udf_warp_config->udf_file_path);
            continue;
        }
        UDF_WARP_TARGET_HELPER* helper = warp_target_helper + i;
        const uint16_t* num_targets = &helper->num_targets;
        if (target->file_info->content_inline)
        {
            content_inline_handler.num_warp_targets(target, helper);

            size += *num_targets;
        }
        else
        {
            content_parts_handler.num_warp_targets(target, helper);
            size += *num_targets;
        }
        if (*num_targets == 0)
        {
            DEBUG_MSG("Skip a target index %d in %s for num_targets is 0", i, udf_warp_config->udf_file_path);
            continue;
        }
        if (helper->data_length != target->size_to_read)
        {
            DEBUG_MSG("Read size mismatch at target index %d in %s (expected: %ld, got: %ld)", i,
                      udf_warp_config->udf_file_path, target->size_to_read, helper->data_length);
        }
    }
    return size;
}

WARP_FILE udf_generate_warp_file(const UDF_WARP_CONFIG* udf_warp_config)
{
    WARP_FILE warp_file = {0};
    if (!udf_warp_config)
    {
        DEBUG_MSG("udf_warp_config is NULL");
        return warp_file;
    }
    if (!udf_warp_config->targets)
    {
        DEBUG_MSG("udf_warp_config->targets is NULL");
        return warp_file;
    }

    UDF_WARP_TARGET_HELPER* helper_array = calloc(sizeof(UDF_WARP_TARGET_HELPER), udf_warp_config->target_count);
    if (!helper_array)
    {
        LOG_OOM_MSG;
        return warp_file;
    }
    const size_t num_warp_targets = calculate_warp_config_count(udf_warp_config, helper_array);
    if (num_warp_targets == 0)
    {
        DEBUG_MSG("warp_target_size is 0");
        return warp_file;
    }
    WARP_TARGET* warp_targets = malloc(sizeof(WARP_TARGET) * num_warp_targets);
    if (!warp_targets)
    {
        LOG_OOM_MSG;
        free(helper_array);
        return warp_file;
    }
    for (uint16_t i = 0; i < udf_warp_config->target_count; ++i)
    {
        const UDF_WARP_TARGET* udf_target = udf_warp_config->targets + i;
        const UDF_WARP_TARGET_HELPER* helper = helper_array + i;
        if (udf_target->file_info->content_inline)
        {
            content_inline_handler.convert_warp_target(warp_targets + i, udf_target, helper, udf_warp_config);
        }
        else
        {
            content_parts_handler.convert_warp_target(warp_targets + i, udf_target, helper, udf_warp_config);
        }
        i += helper->num_targets;
    }
    free(helper_array);
    const WARP_CONFIG warp_config = {
        .warp_count = num_warp_targets,
        .warp_targets = warp_targets
    };
    warp_file = generate_warp_file(&warp_config);
    free(warp_targets);
    return warp_file;
}
