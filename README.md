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
A positive integer unique to a specific space. Used to define a state, must be
the first item in a structure for that structure to be a space.
``` c
// define macro useful for keeping id of a space consistent everywhere 
#define SENSOR_12_SPACE_ID 12
typedef struct Sensor12Space {
    HiveMapSpaceId id; //must be the first 
    unsigned char sensor_1;
    unsigned char sensor_2;
} Sensor12Space;
```

### HiveMapNode(SPACE)
Macro that requires a space (an example being the one defined above). The macro 
generates a structure that is a node. SPACE is assumed to be valid. All nodes 
have these user facing attributes:
- loc: location of node
- goal-loc: location state changes are trying to get to
- state-received: state received callback
- state(SPACE): state of the space defined above

```
HiveMapNode(Sensor12Space) node;
void state_received_by_node(HivMapLoc, HiveMapSpaceId, void*);

// These fields must be filled out
node.loc = 10;
node.goal_loc = 1;
node.state_received = state_received_by_node; // can be NULL if unavailable
node.state.id = SENSOR_12_SPACE;

// space is Sensor12Space
node.state.sensor_1 = 0;
node.state.sensor_2 = 0;
```

### update-node(HiveMapNode*)
Macro that take takes in a HiveMapNode after the node's state has been updated.
Whether a node actually changed is up to the discression of the developer. 
``` c
node.state.sensor_1 = 4;
update_node(&node);
```

### tick-node(HiveMapNode*)
A node must perform certain tasks periodically for it to receive incoming state 
changes and propogate information. To perform this, tick-node is used. Up to
the discression of the developer to determine how often to invoke tick-node.
```
tick_node(&node);
```

## Examples
Examples can be found in the [examples directory](https://github.com/gregjhansell97/hive-map-c/tree/master/examples).
