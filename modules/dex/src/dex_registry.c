#include <dex_registry.h>


LOG_MODULE_REGISTER(dex_registry);

bool dex_initalize(DexContext* ctx, bool (*send_frame_function)(void*, size_t)) {
    memset(ctx, 0, sizeof(*ctx));
    ctx->n_topic_entries = 0;
    ctx->send_frame_function = send_frame_function;
    return true;
}

bool dex_send_register_topic_frame(DexContext* ctx, uint8_t id, const char* name, DexMessageType mtype) {
    // Message framing
    TopicRegisterMessage message = TopicRegisterMessage_init_zero;
    message.topic_id = id;
    strncpy(message.name, name, MAX_TOPIC_NAME_LEN - 1);
    message.name[MAX_TOPIC_NAME_LEN - 1] = '\0';
    message.mtype = mtype;

    // Serialization
    uint8_t serialization_buffer[TopicRegisterMessage_size];
    size_t message_length;
    serialize_message(
        serialization_buffer,
        sizeof(serialization_buffer),
        &message_length,
        MSG_TOPIC_REGISTER,
        (void*) &message
    );

    // Frame construction
    size_t frame_length = calculate_frame_length(message_length);
    uint8_t frame_buffer[frame_length];
    create_dex_frame(
        frame_buffer,
        frame_length,
        MSG_TOPIC_REGISTER,
        serialization_buffer,
        message_length
    );

    // Send the register frame to connected client
    bool result = ctx->send_frame_function(frame_buffer, frame_length);
    return result;
}

bool dex_register_topic(DexContext* ctx, const char* name, DexMessageType mtype, uint8_t* id) {
    // Table full condition
    if ((ctx->n_topic_entries) >= MAX_TOPICS) {
        LOG_ERR("Lookup table full");
        return false;
    }

    // Duplicate entry condition
    for (int i=0; i<(ctx->n_topic_entries); i++) {
        if (!strcmp((ctx->topic_lookup_table)[i].name, name)) {
            LOG_ERR("Entry already exists");
            (*id) = (ctx->topic_lookup_table)[i].id;
            return false;
        }
    }

    if (!dex_send_register_topic_frame(ctx, (ctx->n_topic_entries), name, mtype)) {
        LOG_ERR("Unable to register topic on client side");
        return false;
    }

    TopicLookupEntry entry;
    entry.id = (ctx->n_topic_entries);
    strncpy(entry.name, name, MAX_TOPIC_NAME_LEN - 1);
    entry.name[MAX_TOPIC_NAME_LEN - 1] = '\0';
    entry.mtype = mtype;

    (ctx->topic_lookup_table)[(ctx->n_topic_entries)] = entry;

    (*id) = (ctx->n_topic_entries)++;
    return true;
}

bool dex_get_id_by_name(const DexContext* ctx, const char* name, uint8_t* id) {
    for (int i=0; i<(ctx->n_topic_entries); i++) {
        if (!strcmp((ctx->topic_lookup_table)[i].name, name)) {
            (*id) = (ctx->topic_lookup_table)[i].id;
            return true;
        }
    }

    LOG_ERR("Entry not found");
    return false;
}

bool dex_get_name_by_id(const DexContext* ctx, uint8_t id, char* buffer, size_t buffer_length) {
    if (buffer_length == 0) {
        LOG_ERR("Buffer length is zero");
        return false;
    }
    
    if (id >= (ctx->n_topic_entries)) {
        LOG_ERR("ID not found");
        return false;
    }
    
    strncpy(buffer, (ctx->topic_lookup_table)[id].name, buffer_length - 1);
    buffer[buffer_length - 1] = '\0';
    return true;
}

bool dex_get_mtype_by_id(const DexContext* ctx, uint8_t id, DexMessageType* mtype) {
    if (id >= (ctx->n_topic_entries)) {
        LOG_ERR("ID not found");
        return false;
    }
    
    (*mtype) = (ctx->topic_lookup_table)[id].mtype;
    return true;
}
