#include "roombaBehaviour.hpp"
#include <iostream>


RoombaController* RoombaBehaviour::roombaController=0;
LocalMap* RoombaBehaviour::localMap=0;
pthread_mutex_t RoombaBehaviour::mutexGUIData = PTHREAD_MUTEX_INITIALIZER;


bool RoombaBehaviour::isRunning=true;

RoombaBehaviour::RoombaBehaviour(RoombaController *roombaController,LocalMap* localMap)
{
    RoombaBehaviour::roombaController = roombaController;
    RoombaBehaviour::localMap= localMap;
    startThread();
}

void RoombaBehaviour::startThread()
{
    int iret1 = pthread_create( &roombaBehaviourThread, NULL, behaviourLoop, 0);

    if(iret1)
    {
        fprintf(stderr,"Error - RoombaBehaviour pthread_create() return code: %d\n",iret1);

    }
    else{
        cout<<"roomba Behaviour thread started\n";

    }
}

void *RoombaBehaviour::behaviourLoop(void *arg)
{

    while(isRunning){
        uint8_t lb = roombaController->readLightBumps();
uint16_t ca = roombaController->readBattCapacity();
            uint16_t ch = roombaController->readBattCharge();

//        uint8_t bwd = roombaController->readBumpsnWheelDrops();

//        if(lb!=0){
//            usleep(1000);
//            lb = roombaController->readLightBumps();
//            if(lb!=0)//double check
//            {
//                roombaController->drive(50,1);
//                usleep(1000000);
//            }


//        }else
//        {
//            roombaController->drive(50,32767);
//        }
         localMap->bat=(100*ch/++ca);

        localMap->lightBumps=lb;
        //localMap->Refresh();
        usleep(15000);
    }
}
