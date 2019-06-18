
#ifndef LOCALMAP_HPP
#define LOCALMAP_HPP
#include <stdio.h>
#include <pthread.h>
#include <cstring>
#include <vector>
#include <stdint.h>
#include "roombaController.hpp"

using namespace std;

class LocalMap
{
    typedef struct Point {uint8_t x; uint8_t y;} Point;
public:
void updateObstacles();
private:
vector<Point> obstacles;


int16_t previousXmm;
int16_t previousYmm;

};






#endif //LOCALMAP_HPP

