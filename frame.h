#ifndef FRAME_H
#define FRAME_H

#include <graphics.h>

typedef struct{
int xDos;
int yDos;
} Frame;

Frame makeFrame(int x, int y);
int getXDos(Frame *frame, int xFrame);
int getYDos(Frame *frame, int yframe);

#endif
