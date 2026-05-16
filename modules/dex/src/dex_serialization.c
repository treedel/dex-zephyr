#include <dex_serialization.h>


LOG_MODULE_REGISTER(dex_serialization);

bool serialize_message(void* buffer, size_t buffer_length, size_t* message_length, DexMessageType mtype, void* message) {  
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_length);
    bool result = false;
    switch (mtype) {
        case MSG_TOPIC_REGISTER:
            result = pb_encode(&stream, TopicRegisterMessage_fields, message);
            *message_length = stream.bytes_written;
            break;
        
        default:
            LOG_ERR("Unknown message type");
            return false;
    }
    if (!result) {
		LOG_ERR("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return false;
	}
    return true;
}
