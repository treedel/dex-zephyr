#ifndef DEX_REGISTRY_H
#define DEX_REGISTRY_H

#include <stdint.h>
#include <string.h>

#include <zephyr/logging/log.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/topic_register.pb.h"

#include <tcp.h>
#include <dex_framing.h>
#include <dex_serialization.h>

#include <dex_frame_types.h>


#define MAX_TOPICS          8
#define MAX_TOPIC_NAME_LEN  16

typedef struct TopicLookupEntry {
    uint8_t id;
    char name[MAX_TOPIC_NAME_LEN];
    DexMessageType mtype;
} TopicLookupEntry;

typedef struct DexContext {
    uint8_t n_topic_entries;
    TopicLookupEntry topic_lookup_table[MAX_TOPICS];
    bool (*send_frame_function)(void*, size_t);
} DexContext;

bool dex_initalize(DexContext* ctx, bool (*send_frame_function)(void*, size_t));
bool dex_send_register_topic_frame(DexContext* ctx, uint8_t id, const char* name, DexMessageType mtype);

bool dex_register_topic(DexContext* ctx, const char* name, DexMessageType mtype, uint8_t* id);
bool dex_get_id_by_name(const DexContext* ctx, const char* name, uint8_t* id);
bool dex_get_name_by_id(const DexContext* ctx, uint8_t id, char* buffer, size_t buffer_length);
bool dex_get_mtype_by_id(const DexContext* ctx, uint8_t id, DexMessageType* mtype);

#endif