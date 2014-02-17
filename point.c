//
//  Point.c
//  
//
//  Created by Muhammad S Maromi on 2/17/14.
//
//

#include "point.h"

Point makePoint(int x, int y) {
    Point point;
    
    point.xFrame = x;
    point.yFrame = y;
    
    return point;
}

void drawPoint(Point *point, Frame *frame) {
    putpixel(getXDos(frame, point->xFrame), getYDos(frame, point->yFrame), BLUE);
}