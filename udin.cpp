#include "graphics.h"
#include "stdio.h"
#include "math.h"
#include "conio.h"
#include "dos.h"
#include "stdlib.h"

#define ROUND(a) ((int) (a+0.5))

int graphdriver=DETECT, graphmode,x;

//-- TIPE DATA --
typedef struct{
	int absis;
	int ordinat;
}Point;
//---------------

void lineDDA(Point P1, Point P2, int COLOR){
	int xa,xb,ya,yb;
	//--------------
	xa= P1.absis;
	xb= P2.absis;
	ya= P1.ordinat;
	yb= P2.ordinat;
	//--------------
	int dx=xb-xa;
	int dy=yb-ya;
	int steps;
	int k;
	float xIncrement, yIncrement;
	float x=xa;
	float y=ya;

	if(abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	xIncrement = dx/(float) steps;
	yIncrement = dy/(float) steps;

	putpixel(ROUND(x), ROUND(y), COLOR);
	for(k=0; k<steps;k++){
		x+=xIncrement;
		y+=yIncrement;
		putpixel(ROUND(x),ROUND(y), COLOR);
	}
}

void lineBRES(int x1,int y1,int x2,int y2, int COLOR){
       /*
	int x1,x2,y1,y2;

	x1=P1.absis;
	x2=P2.absis;
	y1=P1.ordinat;
	y2=P2.ordinat;
	 */
	int dx = abs(x1-x2);
	int dy = abs(y1-y2);
	//PARAMETER PEMILIHAN YANG DIPAKAI -> P, 2dy, 2dy - 2dx
	int P = (2*dy) -dx;
	int Ddy = 2 * dy;
	int Ddydx = 2 * (dy-dx);

	// variabel buat ngitung2
	int x,y,xEnd;
	if(x1 > x2){
		x = x2;
		y = y2;
		xEnd = x1;
	}else {
		x = x1;
		y = y1;
		xEnd = x2;
	}
	// titik awal ------
	putpixel(x,y,COLOR);

	while (x < xEnd){
		x++;
		if (P < 0) P += Ddy;
		else {
			y++;
			P += Ddydx;
		}
		putpixel(x,y,COLOR);
	}
}

void circleBRES(Point P1, int r,int color){
	// X dan Y awal
	// asumsi pusat di (0,0) dan jari-jari selalu INT
	// X awal = 0;
	// Y awal = radius (penggambaran searah jarum jam, dari (X,Y) = (0,R)
	int X = 0;
	int Y = r;
	int p = 1-r;

	int xc,yc;
	xc = P1.absis;
	yc = P1.ordinat;

	void gambar(int,int,int,int,int );

	//gambar titik pertama;
	gambar(xc, yc, X, Y, color);

	while(X<Y){
		X++;
		if (p<0){
			p = p + (2*X) +1;
		}else {
			Y--;
			p = p + (2*X) + 1 - (2*Y);
		}
		gambar(xc,yc, X,Y,color);
	}
}

void gambar(int xc, int yc, int X, int Y,int color){
	putpixel(xc+X, yc+Y, color);
	putpixel(xc+X, yc-Y, color);
	putpixel(xc-X, yc+Y, color);
	putpixel(xc-X, yc-Y, color);
	putpixel(xc+Y, yc+X, color);
	putpixel(xc+Y, yc-X, color);
	putpixel(xc-Y, yc+X, color);
	putpixel(xc-Y, yc-X, color);
}


void drawEllipse(float xc, float yc, float x, float y,int color)
{
	putpixel(xc+x, yc+y, color);
	putpixel(xc-x, yc+y, color);
	putpixel(xc+x, yc-y, color);
	putpixel(xc-x, yc-y, color);
}

void ellipseMidpoint(int xc, int yc, int rx, int ry, int color){
	float rxSq = rx * rx;
	float rySq = ry * ry;
	float x = 0, y = ry, p;
	float px = 0, py = 2 * rxSq * y;

	drawEllipse(xc, yc, x, y, color);

	//Region 1
	p = rySq - (rxSq * ry) + (0.25 * rxSq);

	while (px < py){
		x++;
		px = px + 2 * rySq;
		if (p < 0) 	p = p + rySq + px;
		else{
		y--;
		py = py - 2 * rxSq;
		p = p + rySq + px - py;
		}
		drawEllipse(xc, yc, x, y, color);
	}

	//Region 2
	p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
	while (y > 0){
		y--;
		py = py - 2 * rxSq;
		if (p > 0) p = p + rxSq - py;
		else{
			x++;
			px = px + 2 * rySq;
			p = p + rxSq - py + px;
		}
		drawEllipse(xc, yc, x, y, color);
	}
}

void boundaryFill4(Point P1,int fill, int boundary){
	int current;

	Point Pa,Pb,Pc,Pd;
	Pa.absis = P1.absis;
	Pb.absis = P1.absis;
	Pc.absis = P1.absis;
	Pd.absis = P1.absis;
	Pa.ordinat = P1.ordinat;
	Pb.ordinat = P1.ordinat;
	Pc.ordinat = P1.ordinat;
	Pd.ordinat = P1.ordinat;

	current = getpixel(P1.absis,P1.ordinat);
	if((current != boundary) && (current != fill)){
		delay(1);
		putpixel(P1.absis,P1.ordinat,fill);
		Pa.absis++;
		boundaryFill4(Pa,fill, boundary);
		Pb.ordinat++;
		boundaryFill4(Pb,fill, boundary);
		Pc.absis--;
		boundaryFill4(Pc,fill, boundary);
		Pd.ordinat--;
		boundaryFill4(Pd,fill, boundary);
	}
}

void floodFill4(int x, int y, int fill, int oldColor){
	if(getpixel(x,y) == oldColor){
		putpixel(x,y, fill);
		floodFill4(x+1, y, fill, oldColor);
		floodFill4(x-1, y, fill, oldColor);
		floodFill4(x, y+1, fill, oldColor);
		floodFill4(x, y-1, fill, oldColor);
	}
}

void Rec(Point P1, Point P2, Point P3, Point P4, int COLOR){
	lineDDA(P1,P2,COLOR);
	lineDDA(P2,P3,COLOR);
	lineDDA(P3,P4,COLOR);
	lineDDA(P1,P4,COLOR);
}

Point getPixLoc(Point P1){
	Point Ptemp;
	Ptemp.absis = P1.absis + 330;
	Ptemp.ordinat =  - P1.ordinat + 240;
	return Ptemp;
}

void initCanvas(){
	clrscr();
	Point h1,h2,v1,v2,pusKor, SS1,SS2,SS3,SS4;
	h1.absis=20;
	h1.ordinat=240;
	h2.absis = 620;
	h2.ordinat = h1.ordinat;

	v1.absis = 330;
	v2.absis = v1.absis;
	v1.ordinat = 20;
	v2.ordinat = 450;

	pusKor.absis = v1.absis;
	pusKor.ordinat = h1.ordinat;

	SS1.absis = 10;
	SS1.ordinat = 10;
	SS2.absis = 630;
	SS2.ordinat = SS1.ordinat;
	SS3.absis = SS2.absis;
	SS3.ordinat =460;
	SS4.absis = SS1.absis;
	SS4.ordinat = SS3.ordinat;

	int i,j,xS,yS,xF,yF;
	xS = 0; xF=641;
	yS = 0; yF=459;

	for (j=yS;j<=yF;j++){
		for(i=xS;i<=xF;i++){
			putpixel(i,j,BLACK);
		}
	}
	Rec(SS1,SS2,SS3,SS4,BLUE);

	lineDDA(h1,h2,WHITE);
	lineDDA(v1,v2,WHITE);
	circleBRES(pusKor,3,RED);
	boundaryFill4(pusKor, RED,RED);

}

void lineInteractive(){
	Point P1,P2;
	int algo;

	printf("Absis P1 =");
	scanf("%d",&P1.absis);
	printf("Ordinat P1 =");
	scanf("%d",&P1.ordinat);
	printf("Absis P2 =");
	scanf("%d",&P2.absis);
	printf("Ordinat P2 =");
	scanf("%d",&P2.ordinat);

	P1=getPixLoc(P1);
	P2=getPixLoc(P2);

	printf("\nBerikut algoritma yang tersedia\n");
	printf("1. DDA\n");
	printf("2. BRESENHAM\n");
	printf("Pilihan Anda :"); scanf("%d",&algo);

	if(algo==1){
		printf("\nAnda akan menggambar garis dengan algoritma");
		printf(" DDA\nPRESS ANY KEY TO CONTINUE...");
		getch();
		initCanvas();
		lineDDA(P1,P2,GREEN);
	}else if(algo==2){
		printf("\nAnda akan menggambar garis dengan algoritma");
		printf(" BRESENHAM\nPRESS ANY KEY TO CONTINUE...");
		getch();
		initCanvas();
		lineBRES(P1.absis,P1.ordinat,P2.absis,P2.ordinat,GREEN);
	}else{
		printf("Masukan Salah, program akan keluar");
	}
	getch();
}

void circleInteractive(){
	Point pusat;
	int r;
	printf("Absis titik pusat ="); scanf("%d",&pusat.absis);
	printf("Ordinat titik pusat ="); scanf("%d",&pusat.ordinat);
	printf("Masukkan jari-jari lingkaran ="); scanf("%d",&r);

	initCanvas();
	pusat=getPixLoc(pusat);
	circleBRES(pusat,r,GREEN);
}

void elipsInteractive(){
	int rh,rv,xc,yc;
	Point pusat;
	printf("Absis titik pusat ="); scanf("%d",&pusat.absis);
	printf("Ordinat titik pusat =");scanf("%d",&pusat.ordinat);
	printf("Jari-jari horizontal =");scanf("%d",&rh);
	printf("Jari-jari vertikal =");scanf("%d",&rv);

	pusat=getPixLoc(pusat);

}

void bezierCurve(int x[4], int y[4])
{
    int gd = DETECT, gm;
    int i;
    double t;

    initgraph (&gd, &gm, "..\\bgi");

    for (t = 0.0; t < 1.0; t += 0.0005)
    {
	double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] +
		    3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];

	double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] +
		    3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];

	putpixel (xt, yt, WHITE);
	delay(1);
    }

    for (i=0; i<4; i++)
	putpixel (x[i], y[i], YELLOW);

    getch();
    closegraph();
    return;
}

void curveInteractive(){
    int x[4], y[4];
    int i;

    printf ("Enter the x- and y-coordinates of the four control points.\n");
    for (i=0; i<4; i++)
	scanf ("%d%d", &x[i], &y[i]);

    bezierCurve(x, y);
}

int main(){
	int menu;
	menu =0;
	initgraph(&graphdriver, &graphmode, "..\\bgi");

	printf("---> GRAFIKA ~ GRAFIKA ~ GRAFIKA <---\n");
	printf("Berikut menu yang tersedia :\n");
	printf("1. Garis\n");
	printf("2. Lingkaran\n");
	printf("3. Elips\n");
	printf("4. Curve\n");
	printf("10. Exit\n");
	printf("Pilihan Anda : ");
	scanf("%d", &menu);

	printf("Inilah pilihan anda : %d\n\n",menu);

	switch(menu){
		case 1:
			lineInteractive();
			break;
		case 2:
			circleInteractive();
			break;
		case 3:
			elipsInteractive();
			break;
		case 4:
			curveInteractive();
			break;
		case 10:
			printf("THANKS :D");break;
		default:
			printf("Masukan salah, program akan keluar\n");
			break;
	}

	/*
	lineDDA(10,50,200,200);
	lineDDA(220,200, 310,50);
	lineDDA(10,210,200,210);
	lineDDA(10,220,10,300);

	lineBRES(10,350, 200,500);
	lineBRES(220,500, 310,350);

	lineBRES(10,510, 200,510);
	lineBRES(10,520, 10,600);

	circleBRES(200,200,100);

	ellipseMidpoint(100,100, 80, 40);
	*/

	getch();
	return 0;
}
