#ifndef HIVE_MAP_C_HIVE_MAP_H_
#define HIVE_MAP_C_HIVE_MAP_H_

#include <stddef.h>

typedef unsigned char hmap_channel;
typedef unsigned char hmap_space;

struct HiveMapChannel {
    void(*write)(void*, size_t); //msg, size
    void(*read)(void*, size_t);
};

struct HiveMapSpace {
    unsigned char id;
    size_t size;
}

HiveMapNode {
    HiveMapSpace* state;
    unsigned int loc;
    unsigned int goal;
    void(*state_received)(
            unsigned int, 
            HiveMapSpace, 
            void*); //loc & data
    HiveMapChannel** channels;
    byte channels_len;
}
void set_channels(
        HiveMapNode* node, 
        HiveMapChannel** channels, 
        size_t len);
void update_state(HiveMapNode* node);

HiveMapNode** __nodes__ = NULL;
unsigned char __nodes_len__ = 0;
void add_nodes(
        HiveMapNode** nodes, 
        unsigned char len);

void hive_map_tick();

#endif // HIVE_MAP_C_HIVE_MAP_H_
