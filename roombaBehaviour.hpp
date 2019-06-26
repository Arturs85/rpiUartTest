
#ifndef ROOMBABEHAVIOUR_HPP
#define ROOMBABEHAVIOUR_HPP
#include <stdio.h>
#include <pthread.h>
#include <cstring>
#include <vector>
#include <stdint.h>
#include "roombaController.hpp"
#include "localMap.hpp"
#include "logfilesaver.hpp"

using namespace std;

class RoombaBehaviour
{
public:
    RoombaBehaviour(RoombaController* roombaController,LocalMap* localMap);
    ~RoombaBehaviour();
    static bool isRunning;
private:
    static LogFileSaver* logFileSaver;
    static RoombaController* roombaController;
    static LocalMap* localMap;
    pthread_t roombaBehaviourThread;
    static pthread_mutex_t mutexGUIData;

    void startThread();
    static void* behaviourLoop(void* arg);

};






#endif //ROOMBABEHAVIOUR_HPP

