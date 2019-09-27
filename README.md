# Hive-Map-C

C library for [Hive-Map](https://github.com/gregjhansell97/hive-map)

# Examples
``` c
#include "hive_map.h"

void serial_write(char* data, size_t) {
    //provide the ability to write data serially
}
void serial_read(char* data, size_t) {
    //provide the ability to read data serially
}
HiveMapChannel serial_channel = {
    .write = &serial_write,
    .read = &serial_read
};


#define SENSOR_12_SPACE_ID 10
struct Sensor12Space {
    HiveMapSpaceId id;
    unsigned char sensor_1;
    unsigned char sensor_2;
}
    
HiveMapNode(Sensor12Space) node;
state_received_by_node(unsigned int loc, HiveMapSpaceId id, void* raw_state) {
    //handle state changes
    if(loc == 5) { // arbitrary location
        if(id == SENSOR_12_SPACE_ID) {
            Sensor12Space* state = (Sensor12Space*)raw_state;
            node.state.sensor_1 = state->sensor_1; // changes nodes state
            hive_map_update(node); // made changes to nodes state, need to update
        }
    }
}
int main() {
    node.state = {
        .id = SENSOR_12_SPACE_ID,
        .sensor_1 = 0,
        .sensor_2 = 0,
    };
    node.loc = LOC;
    node.goal_loc = GOAL;
    node.state_received = &state_received_by_node;
    set_channels(node, [&serial_channel], 1);
    
    while(1) {
        usleep(1000);
        hive_map_tick(node);
    }
}
```
