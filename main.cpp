
#include "uartTest.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <linux/input.h>
#include <sstream>
#include <vector>

int main(int argc, char** argv)
{
        printf("main started\n");
      
UartTest uartTest;
uartTest.initialize();
//uartTest.send();
uartTest.startReceiveing();
std::string tmp = "test data";
char *arr = &tmp[0];
//uartTest.setDataToTransmit(arr, 9);
//keyboard reading

while(1){
	std::string mystr;
  printf( "enter chars!\n");
  getline (cin, mystr);
	vector<uint8_t> comm;
	
	
std::istringstream ss(mystr);
	cout<<"you entered: ";

while(!ss.eof())
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
comm.clear();
	
	}
uartTest.waitUartThreadsEnd();

  return 0;
}

