
#include "uartTest.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <linux/input.h>
#include <sstream>
#include <vector>
#include "roombaController.hpp"
#include "roombaBehaviour.hpp"

int main(int argc, char** argv)
{
    printf("main started\n");

    UartTest uartTest;
    uartTest.initialize();

    //uartTest.send();
    uartTest.startReceiveing();//starts receiving and sending threads

    RoombaController roombaController(&uartTest);
    RoombaBehaviour* roombaBehaviour;
    std::string tmp = "test data";
    char *arr = &tmp[0];

    //uartTest.setDataToTransmit(arr, 9);
    //keyboard reading


    while(1){
        std::string command;
        getline (cin, command);

        if(!command.compare("raw")){
            std::string mystr;
            printf( "enter chars!\n");
            getline (cin, mystr);
            vector<uint8_t> comm;


            std::istringstream ss(mystr);
            cout<<"you entered: "<<mystr;

            while(!ss.eof())// read integers from string
            {
                int i;
                if(ss>>i)
                {
                    comm.push_back(i);
                    cout<< i<<" ";
                }
            }

            cout<<"\n";

            char *ar = &mystr[0];
            //printf("first char you entered: %d", (uint8_t)(*ar));
            //uartTest.setDataToTransmit(ar, mystr.size());
            uartTest.setDataToTransmit(comm);

            if(comm[0]==142 && comm[1]==25){
                vector<uint8_t> ch = uartTest.readNumberOfBytes(2);
                cout<<"vector ch size: "<<ch.size()<<"\n";
                if(ch.size()==2)
                {//convertData

                    uint16_t* batCharge = reinterpret_cast<uint16_t*>(&ch[0]);
                    cout<<"bat charge received: "<<*batCharge<<"mAh\n";
                }
            }

            else if(comm[0]==142 && comm[1]==26){
                vector<uint8_t> ch = uartTest.readNumberOfBytes(2);
                cout<<"vector ch size: "<<ch.size()<<"\n";
                if(ch.size()==2)
                {//convertData

                    uint16_t* batCapacity = reinterpret_cast<uint16_t*>(&ch[0]);
                    cout<<"bat capacity received: "<<*batCapacity<<"mAh\n";
                }
            }

            comm.clear();
        }
        else if(!command.compare("bat")){
            uint16_t ca = roombaController.readBattCapacity();
            uint16_t ch = roombaController.readBattCharge();

            cout<<"batt ca: "<<ca<< ", ch: "<<ch<<" left: "<<(100*ch/++ca)<<" %\n";
        }
        else if(!command.compare("turn r")){
            roombaController.drive(50,-1);
        }
        else if(!command.compare("stop")){
            roombaBehaviour->isRunning=false;
            roombaController.drive(0,0);
        }
        else if(!command.compare("dist")){
            int16_t dist = roombaController.readDistance();
            cout<<"distance: "<<dist;
        }
        else if(!command.compare("angle")){
            int16_t ang = roombaController.readAngle();
            cout<<"angle: "<<ang;
        }
        else if(!command.compare("lbumps")){
            uint8_t lb = roombaController.readLightBumps();
            cout<<"light bumps: "<<lb;
        }
        else if(!command.compare("roam")){
            roombaBehaviour = new RoombaBehaviour(&roombaController);
        }
    }
    uartTest.waitUartThreadsEnd();

    return 0;
}

