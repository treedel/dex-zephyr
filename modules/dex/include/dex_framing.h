#ifndef DEX_FRAMING_H
#define DEX_FRAMING_H

#include <zephyr/logging/log.h>

#include <stddef.h>
#include <stdint.h>

#include "proto/topic_register.pb.h"
#include <dex_frame_types.h>


#define START_BYTE 0xDE

typedef struct __packed {
    uint8_t start_byte;
    uint16_t length;
    DexFrameType frame_type;
} DexFrameHeader;

size_t calculate_frame_length(size_t payload_length);
size_t create_dex_frame(void* buffer, size_t buffer_length, DexFrameType frame_type, void* payload, size_t payload_length);

#endif