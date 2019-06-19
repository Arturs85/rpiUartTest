#include "roombaController.hpp"
#include <iostream>


RoombaController::RoombaController(UartTest *uartDevice)
{
    cout<<"roomba controller constructor\n";
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
        return *data;
    }
    else return 0;
    

}

uint8_t RoombaController::readBumpsnWheelDrops()
{
    uint8_t* data;
    uartDevice->setDataToTransmit(bumpsRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(1);
    // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==1)
    {//convertData

        data = reinterpret_cast<uint8_t*>(&ch[0]);
        //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
        return *data;
    }
    else return 0;

}

uint16_t RoombaController::readBattCapacity()
{
    uartDevice->setDataToTransmit(battCapacityRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
    // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData
        return readUint16(reinterpret_cast<uint8_t*>(&ch[0]));
    }
    else return 0;
    
}


uint16_t RoombaController::readBattCharge()
{
    uartDevice->setDataToTransmit(battChargeRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
    // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData
        return readUint16(reinterpret_cast<uint8_t*>(&ch[0]));


    }
    else return 0;
    



}

int16_t RoombaController::readDistance()
{
    uartDevice->setDataToTransmit(distanceRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
    // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData

        return readInt16 (reinterpret_cast<uint8_t*>(&ch[0]));
        //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
    }
    else return 0;

}

int16_t RoombaController::readAngle()
{
    uartDevice->setDataToTransmit(angleRequest);

    vector<uint8_t> ch = uartDevice->readNumberOfBytes(2);
    // cout<<"vector ch size: "<<ch.size()<<"\n";
    if(ch.size()==2)
    {//convertData
        return readInt16 (reinterpret_cast<uint8_t*>(&ch[0]));

    }
    else return 0;

}

void RoombaController::drive(int16_t velocity, int16_t radius)
{
    uint8_t array[5]={137,*(reinterpret_cast<uint8_t*>(&velocity)+1),*(reinterpret_cast<uint8_t*>(&velocity)),*(reinterpret_cast<uint8_t*>(&radius)+1),*(reinterpret_cast<uint8_t*>(&radius))};
    char* pt = reinterpret_cast<char*>(array);
    uartDevice->setDataToTransmit(pt,5);// +1 lai nesūta nulles pirms '137' kommandas
    cout<<"first command byte: "<<(*(pt))+0;
}

void RoombaController::sevenSegmentDisplay(uint8_t number)
{

}

void RoombaController::startSafe()
{
    uartDevice->setDataToTransmit(startSafeRequest);
}

void RoombaController::startFull()
{
    uartDevice->setDataToTransmit(startFullRequest);

}

void RoombaController::shutDown()
{
    uartDevice->setDataToTransmit(endRequest);
cout<<"sent power off command\n";
}

int16_t RoombaController::readInt16(uint8_t* beData)
{
    uint8_t leData[2]={beData[1],beData[0]};
    int16_t* data = reinterpret_cast<int16_t*>(&leData[0]);
    //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
    return *data;

}

uint16_t RoombaController::readUint16(uint8_t* beData)
{
    uint8_t leData[2]={beData[1],beData[0]};
    uint16_t* data = reinterpret_cast<uint16_t*>(&leData[0]);
    //cout<<"bat charge received: "<<*batCharge<<"mAh\n";
    return *data;

}
