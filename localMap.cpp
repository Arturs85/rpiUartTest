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
    //if(lightBumps&LTB_R)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+241/SCALE, MAP_SIZE_PX/2-65/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    //if(lightBumps&LTB_FR)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+176/SCALE, MAP_SIZE_PX/2-176/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    //if(lightBumps&LTB_CR)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2+65/SCALE, MAP_SIZE_PX/2-241/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    //if(lightBumps&LTB_CL)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-64/SCALE, MAP_SIZE_PX/2-241/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    //if(lightBumps&LTB_FL)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-176/SCALE, MAP_SIZE_PX/2-176/SCALE), CELL_SIZE_MM/SCALE /* radius */ );
    //if(lightBumps&LTB_L)
        //dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-241/SCALE, MAP_SIZE_PX/2-65/SCALE), CELL_SIZE_MM/SCALE /* radius */ );

    for (auto o: obstacles) {
        dc.DrawCircle( wxPoint(MAP_SIZE_PX/2-o.x/SCALE, MAP_SIZE_PX/2-o.y/SCALE), CELL_SIZE_MM/SCALE /* radius */ );

}

    Refresh();
}

void LocalMap::updateObstaclePosition(int16_t dDist, int16_t dAngle)
{
   float dtr = 3.1415926/180;
    for (auto o: obstacles) {
        o.x = o.x * std::cos(dAngle*dtr)+o.y * sin(dAngle*dtr);
        o.y = -o.x * std::sin(dAngle*dtr)+o.y * cos(dAngle*dtr);
        o.x += dDist*cos(dAngle*dtr);
        o.y += dDist*sin(dAngle*dtr);

    }
}

void LocalMap::addObstacles(uint8_t lightBumps)
{
//    int16_t s1 = 31;
//    int16_t s2 = -31;
//    s1 = round32(s1);
//    s2 = round32(s2);
//    Point p(s1,s2);
//    obstacles.insert(p);
//    cout<<s1<<" "<<s2<<" obs size: "<<obstacles.size()<<"\n";

        if(lightBumps&LTB_R)
            obstacles.insert(Point(round32(241),round(65)));
        if(lightBumps&LTB_FR)
            obstacles.insert(Point(round32(176),round32(176)));
        if(lightBumps&LTB_CR)
            obstacles.insert(Point(round32(65),round32(241)));
        if(lightBumps&LTB_CL)
            obstacles.insert(Point(round32(-64),round32(241)));
        if(lightBumps&LTB_FL)
            obstacles.insert(Point(round32(-176),round32(176)));
        if(lightBumps&LTB_L)
            obstacles.insert(Point(round32(-241),round32(65)));

}

