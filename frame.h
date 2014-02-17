#ifndef FRAME_H
#define FRAME_H

#include <graphics.h>

typedef struct{
int xDos;   //x yang dihitung dari layar DOS (positif: kekanan)
int yDos;   //y yang dihitung dari layar DOS (positif: kebawah)
} Frame;

Frame makeFrame(int x, int y);  //x,y dihitung terhadap DOS
int getXDos(Frame *frame, int xFrame);  //xFrame adalah x yang dihitung terhadap koordinat xDos, yDos (positif: kekanan)
int getYDos(Frame *frame, int yframe);  //yFrame adalah y yang dihitung terhadap koordinat xDos, yDos (positif: keatas)


#endif
