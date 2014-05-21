#include "Frame.h"
#include <graphics.h>
#include <conio.h>

void main() {

    Frame frame;
    int graphdriver = DETECT, graphmode, color;
    int i, j;

    initgraph(&graphdriver, &graphmode, "C:\\TC\\BGI");
    frame = makeFrame(100, 100);


    // tcc -eBARCA GRAPHICS.LIB FRAME.C MAIN.C

    /*
    for (j = 0; j < 1000; j++) {
     	putpixel(0 + j, 0 + j, RED);
    }
    */

    printf("Hello, world 3!");
    getch();
}
