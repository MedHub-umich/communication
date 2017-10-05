/******** Bluetooth communication interface *********

ble.h is the interface the wireless task set will use to send things 

*/


typedef struct BlemDeviceStruct
{
    // pins
    // array of data points
    // current Blem status
    // current mode (active, sleep, etc)
} BlemDeviceStruct;

/* initializes the blem
REQUIRES:
  blem: Pointer to our Blem Device for pin sending, etc.
EFFECTS:
  Goes through the initialization process required to open device
  to find other devices and be found
 */
int setupDevice(BlemDeviceStruct* blem);

/* Sends data through the blem
REQUIRES:
  blem: Pointer to our Blem Device for pin sending, etc.
  data: an array of chars of what we want to send
  length: the size of chars in the array, what we want to send 
EFFECTS:
  sends the data through the ble device
 */
int sendData(BlemDeviceStruct* blem, char* data, size_t length);

/* Recieves data through the blem
REQUIRES:
  blem: Pointer to our Blem Device for pin sending, etc.
  data: an array of chars of at least size length
  length: the maximum bytes of data we want to receive
EFFECTS:
  Looks to receive any data and returns the actual number of bytes recieved
 */
int receiveData(BlemDeviceStruct* blem, char* data, size_t length);


// Helpers NOTE: This is separate from our packager
// These are helpers for packaging the data ONLY for the ble protocol, NOT our API
// Packages data sent in and returns new length, buf must have enough space for data + max size

/* Packages raw data to the BLE standard
REQUIRES:
  data: an array of chars to be packaged
  buf: Where we want the packaged data to go, must be size of data + packaging requirements
  dataLength: The length of our data array
EFFECTS:
  Takes the data passed in and appends or prepends any bits needed for BLE communication
  It will return the size of buf after packaging
 */
int packageData(char* data, char* buf, size_t dataLength);

/* Unpackages raw data to the BLE standard
REQUIRES:
  buf: Where we want the unpackaged data to go, must be size of buf
  data: an array of chars to be unpackaged
  dataLength: The length of our buffered array (how much data we received)
EFFECTS:
  Takes the buf passed in and removes any BLE communication packaging to get the "raw data"
  It will return the size the actual raw data
 */
int unpackageData(char* buf, char* data, size_t bufLength);