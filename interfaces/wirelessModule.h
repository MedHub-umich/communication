/******** Bluetooth communication interface *********

wireless.h is the task set used to manage the sending and receiving
of our ble moduele using ble.h

*/

#include "messageService.h"
#include "bleDevice.h"

#define bufferSize 20

typedef struct Blem;
typedef struct Packet; 

// Helper struct to store the concept of a packet to send
struct Packet {
  char* data;
  size_t length;
}

struct WirelessModuleStruct {
  Packet buf[bufferSize];
}

// ************** Init ************** //
// This function sets up the wireless communication.
// This includes creating tasks to read
// from the blem and send to the blem. 
// This class uses the bleDevice.h to interact with the blem
void WirelessInit(WirelessModuleStruct * this);

// ************** Tasks ************** //

// task that handles the recieve from blem
void WirelessModuleRecieveTask(void *);

// task that handles sending data to the blem
void WirelessModuleSendTask(void *);

// task that recieves messages from other modules
void WirelessModuleIncomingMessageTask(void *);

// task sends messages to other modules such as reading directions, alerts, etc.
void WirelessModuleOutgoingMessageTask(void *);