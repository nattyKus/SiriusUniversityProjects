#include <iostream>
#include <vector>
#include "polygon.h"

Point::Point(double x, double y)
{
    X = x;
    Y = y;
}

pointPlace Point::point_in_polygon(int point_number, std::vector<Point> p)
{
    
    bool result = false;
    int j = point_number - 1;
    for (int i = 0; i < point_number; i++) 
    {
        if ((p[i].X == X && p[i].Y == Y) || 
            (((p[i].Y < Y) && (p[j].Y >= Y)) || ((p[j].Y < Y) && (p[i].Y >= Y))) 
            && (p[i].X + (Y - p[i].Y) / (p[j].Y - p[i].Y) * (p[j].X - p[i].X) == X)
        )
            return pointPlace::ON_EDGE;
        if ((((p[i].Y < Y) && (p[j].Y >= Y)) || ((p[j].Y < Y) && (p[i].Y >= Y))) 
            && (p[i].X + (Y - p[i].Y) / (p[j].Y - p[i].Y) * (p[j].X - p[i].X) < X)
        )
            result = !result;                
        j = i;
    }
    if (result) return pointPlace::INSIDE;
    else return pointPlace::OUTSIDE;
}

