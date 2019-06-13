    #include "roombaController.hpp"
	#include <iostream>


RoombaController::RoombaController(UartTest *uartDevice)
{
    this->uartDevice=uartDevice;
}

uint8_t RoombaController::readLightBumps()
{
    uint8_t* data;
    uartDevice->setDataToTransmit(lightBumpsRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(1);
   // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==1)
    {//convertData

        data = reinterpret_cast<uint8_t*>(&ch[0]);
        //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
    }
    else *data =0;
    return *data;

}

uint16_t RoombaController::readBattCapacity()
{
    uint16_t* data;
    uartDevice->setDataToTransmit(battCapacityRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
   // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData

        data = reinterpret_cast<uint16_t*>(&ch[0]);
    }
    else *data =0;
    return *data;
}


uint16_t RoombaController::readBattCharge()
{
    uint16_t* data;
    uartDevice->setDataToTransmit(battChargeRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
   // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData

        data = reinterpret_cast<uint16_t*>(&ch[0]);
        //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
    }
    else *data =0;
    return *data;


}
