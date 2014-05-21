#ifndef __POINT_H_
#define __POINT_H_

typedef struct _Point {
    int x;
    int y;
} Point;

Point  *point_make(int x, int y);
Point   point_make_s(int x, int y);
void    point_free(Point *point);
double  point_distance(Point *pa, Point *pb);
void    point_rotate(Point *p, Point origin, double angle_radian);
void    point_translate(Point *p, int x, int y);

#endif
