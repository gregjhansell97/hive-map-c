# Hive-Map-C

C library for [Hive-Map](https://github.com/gregjhansell97/hive-map)

## Components

### HiveMapChannel
A channel handles reading and writing of data. The structure defined has two
fields: write and read. These fields take in function pointers. 
```c
void serial_write(char* data, size_t len);
void serial_read(char* data, size_t len);
HiveMapChannel c = {
    .write = &serial_write,
    .read = &serial_read
}
```

### HiveMapLoc
A positive integer describing the location of a particular node

### HiveMapSpaceId
A positive integer unique to a specific space. HiveMapSpaceId is used to define 
a state. It must be the first item in a structure for that structure to be a 
space.
``` c
// define macro useful for keeping id of a space consistent everywhere 
#define SENSOR_12_SPACE_ID 12
typedef struct Sensor12Space {
    HiveMapSpaceId space; //must be the first, doesn't have to be named space
    unsigned char sensor_1;
    unsigned char sensor_2;
} Sensor12Space;
```

### HiveMapNode(SPACE)
Macro that requires a space (an example being the one defined above). The macro 
generates a structure that is a node. SPACE is assumed to be valid. All nodes 
have these user facing attributes:
- loc: location of node
- goal_loc: location state changes are trying to get to
- state_received: state received callback
- state(SPACE): state of the space defined above

``` c
HiveMapNode(Sensor12Space) node;
void state_received_by_node(HivMapLoc, HiveMapSpaceId, void*);

// These fields must be filled out before update_node or cycle_node 
node.loc = 10; // HiveMapLoc type of node
node.goal_loc = 1; // HiveMapLoc type of goal location
node.state_received = state_received_by_node; // NULL if unavailable
node.state.space = SENSOR_12_SPACE; // needs to effectively communicate space

// space is Sensor12Space
node.state.sensor_1 = 0;
node.state.sensor_2 = 0;
```

### update_node(HiveMapNode*, size_t)
Macro that take takes in a HiveMapNode after the node's state has been updated.
Whether a node actually changed is up to the discression of the developer. 
``` c
node.state.sensor_1 = 4;
update_node(&node, sizeof(node));
```

### cycle_node(HiveMapNode*, size_t)
A node must perform certain tasks periodically for it to receive incoming state 
changes and propogate information. To perform this, cycle_node is used. It is 
up to the discression of the developer to determine how often cycle_node is
invoked.
``` c
cycle_node(&node, sizeof(node));
```

## Examples
Examples can be found in the [examples directory](https://github.com/gregjhansell97/hive-map-c/tree/master/examples).
