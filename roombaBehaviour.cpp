#include "roombaBehaviour.hpp"
#include <iostream>


RoombaController* RoombaBehaviour::roombaController=0;
bool RoombaBehaviour::isRunning=true;

RoombaBehaviour::RoombaBehaviour(RoombaController *roombaController)
{
    RoombaBehaviour::roombaController = roombaController;
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
        cout<<"rooba Behaviour thread started";

    }
}

void *RoombaBehaviour::behaviourLoop(void *arg)
{

    while(isRunning){
        uint8_t lb = roombaController->readLightBumps();
        uint8_t bwd = roombaController->readBumpsnWheelDrops();

        if(lb!=0){
            usleep(1000);
            lb = roombaController->readLightBumps();
            if(lb!=0)//double check
            {
                roombaController->drive(50,1);
                usleep(1000000);
            }


        }else
        {
            roombaController->drive(50,32767);
        }
        usleep(15000);
    }
}
