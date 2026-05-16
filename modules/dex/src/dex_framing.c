#include <dex_framing.h>


LOG_MODULE_REGISTER(dex_framing);

size_t calculate_frame_length(size_t payload_length) {
    return sizeof(DexFrameHeader) + payload_length;
}

size_t create_dex_frame(void* buffer, size_t buffer_length, DexFrameType frame_type, void* payload, size_t payload_length) {
    size_t message_length = calculate_frame_length(payload_length);
    if (buffer_length < message_length) {
        LOG_ERR("Buffer length is smaller than message size");
        return 0;
    }

    // Constructing header
    DexFrameHeader header;
    header.start_byte = START_BYTE;
    header.frame_type = frame_type;
    header.length = payload_length;

    // Creating frame
    size_t header_length = sizeof(DexFrameHeader);
    memcpy(buffer, &header, header_length);
    memcpy(((uint8_t*) buffer) + header_length, payload, payload_length);

    return message_length;
}