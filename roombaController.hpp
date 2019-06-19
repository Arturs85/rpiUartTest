
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
    const vector<uint8_t> bumpsRequest{142,7};
    const vector<uint8_t> distanceRequest{142,19};
    const vector<uint8_t> angleRequest{142,20};
    const vector<uint8_t> startSafeRequest{128,131};
    const vector<uint8_t> startFullRequest{128,132};
    const vector<uint8_t> endRequest{133};



    RoombaController(UartTest* uartDevice);
    uint8_t readLightBumps();
    uint8_t readBumpsnWheelDrops();

    uint16_t readBattCapacity();
    uint16_t readBattCharge();

    int16_t readDistance();
    int16_t readAngle();

    void drive(int16_t velocity, int16_t radius);
    void sevenSegmentDisplay(uint8_t number);
void startSafe();
void startFull();
void shutDown();
private:
    int16_t readInt16(uint8_t* beData);
    uint16_t readUint16(uint8_t* beData);
    
    UartTest* uartDevice;


};






#endif //ROOMBACONTROLLER_HPP

