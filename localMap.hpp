
#ifndef LOCALMAP_HPP
#define LOCALMAP_HPP
#include <stdio.h>
#include <pthread.h>
#include <cstring>
#include <vector>
#include <stdint.h>
#include "wx/wx.h"
#include "wx/sizer.h"
#include "roombaController.hpp"


using namespace std;

class LocalMap :public wxPanel
{
    static constexpr int CELL_SIZE_MM = 50;
    static constexpr int MAP_SIZE_PX = 500;
    static constexpr int ROOMBA_RADIUS_MM = 160;
    static constexpr uint8_t LTB_L = 1;
    static constexpr uint8_t LTB_FL = 2;
    static constexpr uint8_t LTB_CL = 4;
    static constexpr uint8_t LTB_CR = 8;
    static constexpr uint8_t LTB_FR = 16;
    static constexpr uint8_t LTB_R = 32;

    static constexpr int SCALE = 10; //mm per pixel

    typedef struct Point {float x; float y;} Point;
public:
    uint8_t lightBumps=255;
uint8_t bat =0;
    LocalMap(wxFrame* parent);
    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);
    DECLARE_EVENT_TABLE()

    void updateObstacles(int16_t dDist,int16_t dAngle);

private:
//wxTimer timerForRefresh;
    vector<Point> obstacles;

    int16_t previousXmm;
    int16_t previousYmm;

};





#endif //LOCALMAP_HPP

