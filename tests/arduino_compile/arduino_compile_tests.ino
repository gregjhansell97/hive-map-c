#include "hive_map.h"

void setup()
{
    Serial.begin(250000);
}

void on_write(hmap_channel c, byte* bytes, size_t len) {

  
}

void loop()
{
    HiveMapNode.on_write = on_write;
}
