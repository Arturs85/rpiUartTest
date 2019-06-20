#include "localMap.hpp"
#include <iostream>
#include <wx/timer.h>

LocalMap::LocalMap(wxFrame *parent):wxPanel(parent)
{
	//timerForRefresh(this,TIMER_ID);
//timerForRefresh.Start(100);
}

void LocalMap::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
       render(dc);
}

void LocalMap::paintNow()
{
    wxClientDC dc(this);
      render(dc);
}

void LocalMap::render(wxDC &dc)
{
    // draw some text
    dc.DrawText(wxT("lightBumps: "+std::to_string(lightBumps)), 40, 50);

dc.DrawText(wxT("bat: "+std::to_string(bat)+ "%"), 40, 80);

    // draw a circle
//    dc.SetBrush(*wxGREEN_BRUSH); // green filling
//    dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
//    dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

//    // draw a rectangle
//    dc.SetBrush(*wxBLUE_BRUSH); // blue filling
//    dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
//    dc.DrawRectangle( 300, 100, 400, 200 );

    // draw a line
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // black line, 3 pixels thick

    dc.DrawCircle( wxPoint(MAP_SIZE_PX/2, MAP_SIZE_PX/2), ROOMBA_RADIUS_MM/SCALE /* radius */ );
    dc.DrawLine( MAP_SIZE_PX/2, MAP_SIZE_PX/2, MAP_SIZE_PX/2,MAP_SIZE_PX/2-ROOMBA_RADIUS_MM/SCALE ); // draw line across the rectangle

     dc.SetBrush(*wxGREY_BRUSH); // green filling
    if(lightBumps&LTB_R)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+241/SCALE, MAP_SIZE_PX/2-65/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    if(lightBumps&LTB_FR)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+176/SCALE, MAP_SIZE_PX/2-176/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    if(lightBumps&LTB_CR)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+65/SCALE, MAP_SIZE_PX/2-241/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    if(lightBumps&LTB_CL)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-64/SCALE, MAP_SIZE_PX/2-241/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    if(lightBumps&LTB_FL)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-176/SCALE, MAP_SIZE_PX/2-176/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    if(lightBumps&LTB_L)
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-241/SCALE, MAP_SIZE_PX/2-65/SCALE), CELL_SIZE_MM/SCALE /* radius */ );

    Refresh();
}

void LocalMap::updateObstacles(int16_t dDist, int16_t dAngle)
{
    for (int i = 0; i < obstacles.size(); ++i) {
        obstacles.at(i).x = obstacles.at(i).x * std::cos(dAngle)+obstacles.at(i).y * sin(dAngle);
        obstacles.at(i).y = -obstacles.at(i).x * std::sin(dAngle)+obstacles.at(i).y * cos(dAngle);
    obstacles.at(i).x += dDist*cos(dAngle);
    obstacles.at(i).y += dDist*sin(dAngle);

    }
}

