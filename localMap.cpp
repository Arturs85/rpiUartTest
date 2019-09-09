#include "localMap.hpp"
#include <iostream>
#include <wx/timer.h>

LocalMap::LocalMap(wxFrame *parent):wxPanel(parent)
{
    //timerForRefresh(this,TIMER_ID);
    //timerForRefresh.Start(100);
    fwdButton = new wxButton(this, BUTTON_fwd, _T("fwd"),wxDefaultPosition, wxDefaultSize, 0); // with the text "hello World"
    turnLeftButton = new wxButton(this, BUTTON_left, _T("left"),wxDefaultPosition +wxPoint(0,30), wxDefaultSize, 0); // with the text "hello World"
    stopMovingButton = new wxButton(this, BUTTON_stop, _T("stop"),wxDefaultPosition+wxPoint(0,60), wxDefaultSize, 0); // with the text "hello World"


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
    dc.DrawText(wxT("lightBumps: "+std::to_string(lightBumps)), 20, 150);

    dc.DrawText(wxT("bat: "+std::to_string(bat)+ "%"), 20, 180);

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
    obsTemp.clear();
    float dtr = 3.1415926/70;//should be pi/180, but roomba returns deg/3
 dAngle = -dAngle;
    for (auto o: obstacles) {
        int16_t x = o.x * std::cos(dAngle*dtr)+o.y * sin(dAngle*dtr);
        int16_t y = -o.x * std::sin(dAngle*dtr)+o.y * cos(dAngle*dtr);
        y += 13*dDist*cos(dAngle*dtr);
        x += 13*dDist*sin(dAngle*dtr);
        obsTemp.insert(Point(x,y));
    }
    obstacles=obsTemp;

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

    if(lightBumps&LTB_L)
        obstacles.insert(Point(round32(241),round(65)));
    if(lightBumps&LTB_FL)
        obstacles.insert(Point(round32(176),round32(176)));
    if(lightBumps&LTB_CL)
        obstacles.insert(Point(round32(65),round32(241)));
    if(lightBumps&LTB_CR)
        obstacles.insert(Point(round32(-64),round32(241)));
    if(lightBumps&LTB_FR)
        obstacles.insert(Point(round32(-176),round32(176)));
    if(lightBumps&LTB_R)
        obstacles.insert(Point(round32(-241),round32(65)));

}

void LocalMap::buttonHandler(wxCommandEvent &event)
{
//cout<<"eventId: "<<event.GetId()<<" int: "<<event.GetInt()<<"\n";

if(event.GetId()==BUTTON_fwd)
RoombaController::driveForward();
if(event.GetId()==BUTTON_left)
RoombaController::turnLeft();
if(event.GetId()==BUTTON_stop)
RoombaController::stopMoving();


}


