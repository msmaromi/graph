//
//  line.c
//  
//
//  Created by Muhammad S Maromi on 2/17/14.
//
//

#include "line.h"

Line makeLine(Point p1, Point p2) {
    Line line;
    
    line.point1 = makePoint(p1->xFrame, p1->yFrame);
    line.point2 = makePoint(p2->xFrame, p2->yFrame);
    
    return line;
}

void drawLine(Line *line) {
    //monggo dilanjutkeun
}
