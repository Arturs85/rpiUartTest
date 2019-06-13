
#ifndef ROOMBACONTROLLER_HPP
#define ROOMBACONTROLLER_HPP
#include <stdio.h>
#include <pthread.h>
#include <cstring>
#include <vector>
#include <stdint.h>
#include "uartTest.h"

using namespace std;

class RoombaController
{
public:

    const vector<uint8_t> lightBumpsRequest{142,45};
    const vector<uint8_t> battCapacityRequest{142,26};
    const vector<uint8_t> battChargeRequest{142,25};
RoombaController(UartTest* uartDevice);
    uint8_t readLightBumps();

    uint16_t readBattCapacity();
    uint16_t readBattCharge();
  private:

    UartTest* uartDevice;


};






#endif //ROOMBACONTROLLER_HPP

