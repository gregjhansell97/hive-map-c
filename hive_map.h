#ifndef HIVE_MAP_C_HIVE_MAP_H_
#define HIVE_MAP_C_HIVE_MAP_H_

#include <stddef.h>

typedef unsigned char HiveMapSpaceId;
typedef unsigned int HiveMapLoc;

typedef struct HiveMapChannel {
    void(*write)(char*, size_t); //msg, size
    void(*read)(char*, size_t);
} HiveMapChannel;

struct HiveMapNodeBase {
    HiveMapLoc loc;
    HiveMapLoc goal_loc;
    void(*state_received)(
            HiveMapLoc,
            HiveMapSpaceId,
            void*);
    unsigned char _channels_len;
    HiveMapChannel** _channels;
};

#define HiveMapNode(SPACE)\
struct {\
    HiveMapLoc loc;\
    HiveMapLoc goal_loc;\
    void(*state_received)(\
            HiveMapLoc,\
            HiveMapSpaceId,\
            void*);\
    unsigned char _channels_len;\
    HiveMapChannel** _channels;\
    SPACE state;\
}
void set_node_channels(
        void* node, 
        HiveMapChannel* channels[], 
        size_t len);
void _hive_map_update_node(void* node, size_t size);
void _hive_map_tick_node(void* node, size_t size);
// make it a pointer sizeof(*NODE)?
#define update_node(NODE) _hive_map_update_node(NODE, sizeof(*NODE)) 
#define tick_node(NODE) _hive_map_tick_node(NODE, sizeof(*NODE)) 


#endif // HIVE_MAP_C_HIVE_MAP_H_
