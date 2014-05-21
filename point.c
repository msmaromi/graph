#include <stdlib.h>
#include <math.h>

#include "point.h"

Point *point_make(int x, int y)
{
    Point *p = (Point*) malloc(sizeof(Point));
    p->x = x;
    p->y = y;

    return p;
}

Point point_make_s(int x, int y)
{
    Point p = { x, y };
    return p;
}

void point_free(Point *p)
{
    free(p);
}

double point_distance(Point *pa, Point *pb)
{
    double xab = pa->x - pb->x;
    double yab = pa->y - pb->y;
    
    double distance = sqrt(xab * xab + yab * yab);
    return distance;
}

void point_rotate(Point *p, Point origin, double angle_radian)
{
    Point tmp = point_make_s(p->x, p->y);
    p->x = (tmp.x - origin.x) * cos(angle_radian) - (tmp.y - origin.y) * sin(angle_radian) + origin.x;
    p->y = (tmp.x - origin.x) * sin(angle_radian) + (tmp.y - origin.y) * cos(angle_radian) + origin.y;
}

void point_translate(Point *p, int x, int y)
{
    p->x += x;
    p->y += y;
}
