# Devices

* 2 kinds of devices
    physical
    logical

## Physical

* Physical - the GPU - holds memory and queues to process the data - can't be accessed directly
* Logical - an interface to the physical device - used a lot - set up everything on the GPU

* a physical device interacts with the gpu
* used for memory (image data, vertex data)
* queues -> process commands submitted to the gpu
* phy devices are retrieved, not created

We can enumerate all phy devices from an instance

Can have multiple types of queues (families)

A family can have more than one queue.

### Queue families

Graphucs queue family - for processing graphics
Compute queue family - compute shaders
Transfer queue family - process data transfer

IDs for queues can be the same for different families.

*NOTE* Always check if the phy device has the queues we need. We can query the device as to what families it has.

## Logical

Acts as an interface for the Physical device. Term that gets referenced most. Most objects are created on a logical device.

Usually the first argument to functions.

### Creation

Define queues families - we can create many logical devices for one physical device. We have to tell how many queues the logical device will use.

We need to define the features it needs (geometry shader, etc...)

We also need to define the extensions.