//
//  Point.h
//  
//
//  Created by Muhammad S Maromi on 2/17/14.
//
//

#ifndef _Point_h
#define _Point_h

#include "frame.h"

typedef struct {
    int xFrame;  //dihitung terhadap frame
    int yFrame;  //dihitung terhadap frame
} Point;

Point makePoint(int x, int y);
void drawPoint(Point *point, Frame *frame);


#endif
