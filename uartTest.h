
#ifndef UARTTEST_H
#define UARTTEST_H

#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>	 	//Used for UART
#include <pthread.h>
#include <cstring>
#include <vector>
#include <stdint.h>

using namespace std;

class UartTest
{
public:
static int uart0_filestream;
 pthread_t receivingThreadUart;
 pthread_t sendingThreadUart;
static pthread_mutex_t mutexSend; 
static char tx_buffer[];
static int tx_size;

UartTest();
~UartTest();
void initialize();
void send();
void startReceiveing();
static void setDataToTransmit(char* data, int size);
static void setDataToTransmit(vector<uint8_t> comm);

static void* receive(void* arg);
static void* sendingLoop(void* arg);
void waitUartThreadsEnd();

};






#endif //UARTTEST_H

