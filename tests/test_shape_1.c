#include <stdio.h>
#include <assert.h>
#include "shape.h"
#include "point.h"

#define SHAPE_ID_HELLO 1

int main()
{
    Point *p;
    Shape *hello;

    printf("-- test_shape_1 --\n");

    hello = shape_make(SHAPE_ID_HELLO, point_make_s(0, 0), 10);

    shape_add_point(hello, point_make_s(10, 10));
    shape_add_point(hello, point_make_s(5, 25));
    shape_add_point(hello, point_make_s(8, 18));

    assert(hello->capacity == 10);
    assert(hello->size == 3);
    printf("Shape size: %d\n", hello->size);

    p = &(hello->points[0]);
    assert(p->x == 10 && p->y == 10);
    printf("Point[0]: %d, %d\n", p->x, p->y);

    p++;
    assert(p->x == 5 && p->y == 25);
    printf("Point[1]: %d, %d\n", p->x, p->y);

    p++;
    assert(p->x == 8 && p->y == 18);
    printf("Point[2]: %d, %d\n", p->x, p->y);

    // -------------------------------------------------------------------------
    printf("\nTranslating hello (5, 5)\n");
    shape_translate(hello, 5, 5);

    p = &(hello->points[0]);
    assert(p->x == 15 && p->y == 15);
    printf("Point[0]: %d, %d\n", p->x, p->y);

    p++;
    assert(p->x == 10 && p->y == 30);
    printf("Point[1]: %d, %d\n", p->x, p->y);

    p++;
    assert(p->x == 13 && p->y == 23);
    printf("Point[2]: %d, %d\n", p->x, p->y);

    // -------------------------------------------------------------------------
    printf("\nRotating hello against (5, 5), pi rad\n");
    shape_rotate(hello, point_make_s(5, 5), 3.1415);

    p = &(hello->points[0]);
    printf("Point[0]: %d, %d\n", p->x, p->y);
    p++;
    printf("Point[1]: %d, %d\n", p->x, p->y);
    p++;
    printf("Point[2]: %d, %d\n", p->x, p->y);

    shape_free(hello);
}
