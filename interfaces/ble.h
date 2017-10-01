/******** Bluetooth communication interface *********

The system for wireless communication is two part:

1. Sensors that record and send through information
    -- All they want to do is "send info"
2. The bluetooth task that handles sending and receiving information
    -- It only cares about communicating with the other module, not what
        specifically the info is

Therefore, this is a two part interface. 

wireless.h is the interface for sending information to the bluetooth module
            since it doesn't care HOW it gets sent

ble.h is the interface the Bluetooth LE Module (blem) task will 

*/
typedef struct Blem; // TODO: Figure this syntax out

struct Blem {
  // Todo fill me in
}

// Sets up device and returns positive integer if successful, 0 if unsuccessful
int setupDevice(/* Todo: figure out these parameters */);

// Sends data returns length of number of bytes sent
int sendData(void* data, size_t length);

// Receives up to length bytes of data, returns how much data was actually received
int receiveData(void* data, size_t length);


// Helpers
// Packages data sent in and returns new length, buf must have enough space for data + max size
int packageData(void* data, void* buf, size_t dataLength);

// Takes data sent in and returns the unpackaged part. Returns the new length. Data must be at least buf
int unpackageData(void* buf, void* data, size_t bufLength);