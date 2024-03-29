#include <stdlib.h>
#include <unistd.h>

#include "hive_map.h"

void serial_write(char* data, size_t len) {
    // provide the ability to write data serially
}
void serial_read(char* data, size_t len) {
    // provide the ability to read data serially
}
HiveMapChannel serial_channel = {
    .write = &serial_write,
    .read = &serial_read
};
HiveMapChannel* channels[] = {&serial_channel};

#define SENSOR_12_SPACE_ID 10
typedef struct Sensor12Space {
    HiveMapSpaceId space;
    unsigned char sensor_1;
    unsigned char sensor_2;
} Sensor12Space;

HiveMapNode(Sensor12Space) node;
void state_received_by_node(
        HiveMapLoc loc, 
        HiveMapSpaceId id, 
        void* raw_state) {
    // handle state changes
    if(loc == 5) { // arbitrary location
        if(id == SENSOR_12_SPACE_ID) {
            Sensor12Space* state = (Sensor12Space*)raw_state;
            node.state.sensor_1 = state->sensor_1; // changes node to new state
            update_node(&node, sizeof(node));
        }
    }
}
int main() {
    node.loc = 10;
    node.goal_loc = 1;
    node.state_received = &state_received_by_node;
    // setting state
    node.state.space = SENSOR_12_SPACE_ID;
    node.state.sensor_1 = 0;
    node.state.sensor_2 = 0;
    set_node_channels(&node, channels, 1);

    while(1) {
        usleep(1000);
        cycle_node(&node, sizeof(node));
    }

    exit(EXIT_SUCCESS);
}
