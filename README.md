# communication
The communication for our devices

## Style Guide
1. Comments are put above the function prototype
2. Comment above function that describes function with a bulleted list for parameters

### Sample Function Description
~~~ cpp
/* Send data asynchronously
Parameters:
  - Pointer to the device to register with (global variables bleh)
  - The id is the UNIQUE IDENTIFIER from registerDevice
  - The priority of the data (May be depricated)
  - The pointer to the data. This should be the WHOLE PACKAGE expected to be sent (any packaging outside of BLE stuff should be done prior)
  - The length of the data
  
This function queues data in the blem to be sent in its respective priority. Next data burst will send the data to the connected devices.
It will return the length of number of bits successfully added and negative for an error
*/
int sendDataAsynch(Blem* blem, int id, int priority, void* data, size_t length);
~~~
