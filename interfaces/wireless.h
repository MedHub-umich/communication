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

/****** Admin stuff with device ******/
/* Register self with blem for data receiving
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The name of the device-- most likely only used for debugging a la FreeRTOS tasks
  - The messageType to register the device with, -1 for all data
  - The task handle to wake (probably?) when data is received
MODIFIES:
  - Internal blem structure to track the task
EFFECTS:
  - Registers the function pointer that will be called when info was received. May be a FreeRTOS task handle
  - Returns a positive integer if successful or 0 if not. The return value is the UNIQUE IDENTIFIER for the registration
*/
int registerDevice(Blem* blem, char* name, int messageType, void* task);

/* Unregister self with blem for data receiving
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
MODIFIES:
  - Internal blem structure to remove the task
EFFECTS:
  - Removes the task from the receiving tracking based on the id passed in
*/
int unregisterDevice(Blem* blem, int id);
 
/****** Sending data ********/ 
/* Send data asynchronously
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
  - The priority of the data (May be depricated)
  - The pointer to the data. This should be the WHOLE PACKAGE expected to be sent (any packaging outside of BLE stuff should be done prior)
  - The length of the data
MODIFIES:
  - Adds the data to be sent in the blem struct
EFFECTS:
  - Queues data in the blem to be sent in its respective priority. Next data burst will send the data to the connected devices
  - Returns the length of number of bits successfully added, negative for an error
*/
int sendDataAsynch(Blem* blem, int id, int priority, void* data, size_t length);

/****** Sending data ********/ 
/* Send data synchronously
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
  - If flush is non-zero, it will send everything, else it just sends the data sent through the parameters
  - The pointer to the data. This should be the WHOLE PACKAGE expected to be sent (any packaging outside of BLE stuff should be done prior)
  - The length of the data
  NOTE: The priority is not included since it is implied that synchronous sending is high priority
MODIFIES:
  - If flush, it will remove everything from the queue by sending it
EFFECTS:
  - Queues data in the blem to be sent in its respective priority. Next data burst will send the data to the connected devices
  - Returns the length of number of bits successfully *sent*, negative for an error 
*/
int sendDataSynch(Blem* blem, int flush, int id, void* data, size_t length);

/* Wait to receive data asynchronously
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
  - The semaphore to use to wake up the task
  - The messgeType of data waiting for, -1 for all data
  - The pointer to the pointer of data that will be populated with the data when received
  - The pointer to the variable to store the length returned, should initially be set to an invalid size
MODIFIES:
  - Will register the semaphore and parameters with the blem struct
EFFECTS:
  - Will register the semaphore and populate and raise the semaphore when the correct data is received
  - IT IS THIS TASKS JOB TO GIVE BACK THE DATA WHEN FINISHED
*/
void waitToReceiveAsync(Blem* blem, int id, semaphore* s, int messageType, void** buffer, int* length);

/* Wait to receive data Synchronously
REQUIRES:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
  - The messgeType of data waiting for, -1 for all data
  - The pointer to the pointer of data that will be populated with the data when received
MODIFIES:
  - None
EFFECTS:
  - Will ping the device to check for communications of specific message type. It will return the size of data it got, 0 if no data was found and -1 for an error 
*/
int waitToReceiveSynch(Blem* blem, int id, int messgeType, void** buffer);






 
 