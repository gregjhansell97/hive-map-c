#ifndef HIVE_MAP_C_HIVE_MAP_H_
#define HIVE_MAP_C_HIVE_MAP_H_

#include <stddef.h>

typedef unsigned char hmap_channel;
typedef unsigned char hmap_space;

struct HiveMapNode_t {
   void(*on_write)(hmap_channel, unsigned char*, size_t);
   void(*on_read)(hmap_channel, unsigned char*, size_t);
   void(*on_child)(hmap_space, void*);
   void(*on_peer)(hmap_space, void*);
   void(*on_parent)(hmap_space, void*);
};

struct HiveMapNode_t HiveMapNode = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

void hmap_set_channels(void* channels, size_t len);
void hmap_set_spaces(void* spaces, size_t len);
void hmap_set_state(hmap_space, void* state);

#endif // HIVE_MAP_C_HIVE_MAP_H_
