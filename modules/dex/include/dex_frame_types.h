#ifndef DEX_FRAME_TYPES_H
#define DEX_FRAME_TYPES_H

typedef enum DexFrameType {
    MSG_TOPIC_REGISTER = 0,
    MSG_HEARTBEAT = 1,
    MSG_DATA = 2
} DexFrameType;

#endif