#ifndef DEX_SERIALIZATION_H
#define DEX_SERIALIZATION_H

#include <zephyr/logging/log.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/topic_register.pb.h"

#include <dex_frame_types.h>


bool serialize_message(void* buffer, size_t buffer_length, size_t* message_length, DexMessageType mtype, void* message);

#endif