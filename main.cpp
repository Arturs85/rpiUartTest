
#include "uartTest.h"
	#include "uwbmsglistener.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <linux/input.h>
#include <sstream>
#include <vector>
#include "roombaController.hpp"
#include "roombaBehaviour.hpp"
#include "localMap.hpp"

class MyApp: public wxApp
{
public:
    bool OnInit();

    void OnClose(wxCloseEvent &event);
    wxFrame *frame;
    LocalMap* localMap;
    UartTest uartTest;
    static RoombaBehaviour* roombaBehaviour;
    static RoombaController* roombaController;

public:
    int main(int ac,char**av);

};
IMPLEMENT_APP(MyApp)

RoombaController* MyApp::roombaController=0;
RoombaBehaviour* MyApp::roombaBehaviour=0;


int MyApp::main(int argc, char** av)
{

    printf("main started\n");

    UartTest uartTest;
    uartTest.initialize();

UwbMsgListener uwbMsgListener; // start uwb device
	uwbMsgListener.initialize();

    //uartTest.send();
    uartTest.startReceiveing();//starts receiving and sending threads

    RoombaController roombaController(&uartTest);
    RoombaBehaviour* roombaBehaviour;
    std::string tmp = "test data";
    char *arr = &tmp[0];

    //uartTest.setDataToTransmit(arr, 9);
    //keyboard reading

    while(0){
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
            roombaBehaviour = new RoombaBehaviour(&roombaController,localMap);
        }
    }
    uartTest.waitUartThreadsEnd();

    return 0;
}

void exit_handler(int s){
    printf("Caught signal %d\n",s);
    MyApp::roombaController->shutDown();
    if(MyApp::roombaBehaviour!=0)
        delete(MyApp::roombaBehaviour);
 // uartTest.waitUartThreadsEnd();
    usleep(100000);
    exit(1);

}

void MyApp::OnClose(wxCloseEvent &event){
    roombaController->shutDown();
    cout<<"OnClose called\n";
    //  Destroy();

}

bool MyApp::OnInit()
{

    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);


UwbMsgListener uwbMsgListener; // start uwb device
	uwbMsgListener.initialize();

    uartTest.initialize();
    uartTest.startReceiveing();//starts receiving and sending threads
    roombaController=new RoombaController(&uartTest);
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new wxFrame((wxFrame *)NULL, -1,  wxT("vsmRoomba with wxWidgets"), wxPoint(50,50), wxSize(800,600));

    localMap = new LocalMap( (wxFrame*) frame );
    roombaBehaviour = new RoombaBehaviour(roombaController,localMap);

    sizer->Add(localMap, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show();
    // main(0,0);

    roombaController->startFull();

    roombaController->sevenSegmentDisplay(65);// use display as ON indicator

    return true;
}

BEGIN_EVENT_TABLE(LocalMap, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */
EVT_BUTTON ( BUTTON_left, LocalMap::buttonHandler )
EVT_BUTTON ( BUTTON_fwd, LocalMap::buttonHandler )
EVT_BUTTON ( BUTTON_stop, LocalMap::buttonHandler )


// catch paint events
EVT_CLOSE(MyApp::OnClose)
EVT_PAINT(LocalMap::paintEvent)
//EVT_TIMER(TIMER_ID, LocalMap::OnTimer)
END_EVENT_TABLE()

