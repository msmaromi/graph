#include "point.h"

#ifndef __SHAPE_H_
#define __SHAPE_H_

typedef struct _Shape {
    int id;
    int size;
    int capacity;
    Point pos;
    Point *points;
} Shape;

Shape *shape_make(int shape_id, Point position, int capacity);
void   shape_free(Shape *shape);
void   shape_add_point(Shape *shape, Point p);
void   shape_rotate(Shape *shape, Point origin, double angle_radian);
void   shape_translate(Shape *shape, int x, int y);

#endif
