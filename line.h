//
//  line.h
//  
//
//  Created by Muhammad S Maromi on 2/17/14.
//
//

#ifndef _line_h
#define _line_h

#include "point.h"

typedef struct{
    Point point1;
    Point point2;
} Line;

Line makeLine(Point *p1, Point *p2);
void drawLine(Line *line);

#endif
