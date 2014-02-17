#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>

#include "FRAME.H"

Frame makeFrame(int x, int y) {
    int i, j;

    Frame frame;
    frame.xDos = x;
    frame.yDos = y;

    for( i = 0; i < 1000; i++) {
        putpixel(frame.xDos + i, frame.yDos, RED);
    }

    for (j = 0; j < 1000; j++) {
        putpixel(frame.xDos, frame.yDos + j, RED);
    }

    printf("Hello, world!\n");

    return frame;
}

int getXDos(Frame *frame, int x) {
    return (frame->xDos + x);
}

int getYDos(Frame *frame, int y) {
    return (frame->yDos - y);
}
