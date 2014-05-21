#include <stdlib.h>
#include <math.h>

#include "shape.h"

Shape *shape_make(int shape_id, Point position, int capacity)
{
    Shape *shape = (Shape *) malloc(sizeof(Shape));
    shape->id = shape_id;
    shape->pos = position;
    shape->capacity = capacity;

    shape->size = 0;
    shape->points = (Point *) malloc(capacity * sizeof(Point));
}

void shape_free(Shape *shape)
{
    free(shape->points);
    free(shape);
}

void shape_add_point(Shape *shape, Point p)
{
    int i = shape->size;
    (shape->points[i]).x = shape->pos.x + p.x;
    (shape->points[i]).y = shape->pos.y + p.y;

    shape->size = i + 1;
}

void shape_rotate(Shape *shape, Point origin, double angle_radian)
{
    int i;
    
    origin.x += shape->pos.x;
    origin.y += shape->pos.y;

    for (i = 0; i < shape->size; i++) {
        point_rotate(&(shape->points[i]), origin, angle_radian);
    }
}

void shape_translate(Shape *shape, int x, int y)
{
    int i;

    shape->pos.x += x;
    shape->pos.y += y;

    for (i = 0; i < shape->size; i++) {
        point_translate(&(shape->points[i]), x, y);
    }
}
