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


//HEADER
void boundaryFillInteractive(Point);
//------------------------------

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
/*
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
*/
void boundaryFill4Queue(Point P, int fill, int boundary){
	int ListPointX[10000];
	int ListPointY[10000];
	int current,counter;
	int currentW,currentE;
	Point W;
	Point E;
	Point PP;
	Point temp;
	counter = 0;
	
	for(int i=0;i<1000;i++){
		ListPointX[i] = -2;
		ListPointY[i] = -3;
	}
	
	PP.absis = P.absis;
	PP.ordinat = P.ordinat;
	
	if(ListPointX[counter] == -2){		
		current = getpixel(P.absis, P.ordinat);
		if(current != boundary && current != fill){
			ListPointX[counter] = PP.absis;
			ListPointY[counter] = PP.ordinat;	
			while(ListPointX[counter]  > 0){
				temp.absis = ListPointX[counter];
				temp.ordinat = ListPointY[counter];
				ListPointX[counter] = -2;
				ListPointY[counter] = -3;
				//printf(" %d&%d||%d %d ",ListPointX[counter],ListPointY[counter],temp.absis, temp.ordinat);
				current = getpixel(temp.absis, temp.ordinat);
				if(((current != boundary) && (current != fill) && (temp.absis!=-1)) || counter ==0){
					//geser kanan dan kiri
					W.absis = temp.absis+1;
					//printf(" %d", W.absis);
					E.absis = temp.absis;
					W.ordinat = temp.ordinat;
					E.ordinat = temp.ordinat;
					currentW = getpixel(W.absis, W.ordinat);
					currentE = getpixel(E.absis, E.ordinat);					
					
					int j=counter;
				
					while(currentW != boundary && currentW != fill){
						putpixel(W.absis,W.ordinat,fill);
						if(getpixel(W.absis, W.ordinat+1) != boundary && getpixel(W.absis, W.ordinat+1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat+1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}
						if(getpixel(W.absis, W.ordinat-1) != boundary && getpixel(W.absis , W.ordinat-1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat-1;
							ListPointX[j+1] =PP.absis;
							ListPointY[j+1]= PP.ordinat;
							j++;
						}
						W.absis ++; //geser kanan
						currentW = getpixel(W.absis, W.ordinat);				
						//getch();
					}					

					while(currentE != boundary && currentE != fill){
						putpixel(E.absis,E.ordinat,fill);
						if(getpixel(E.absis, E.ordinat + 1) != boundary && getpixel(E.absis, E.ordinat + 1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat + 1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;	
							j++;
						}
						if(getpixel(E.absis , E.ordinat - 1) != boundary && getpixel(E.absis , E.ordinat -1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat-1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}
						E.absis --; //geser kiri
						currentE = getpixel(E.absis, E.ordinat);
					}
				}
				counter ++;
			}
			printf(" FINISH");
		}
	}
	
}

void floodFill4(int x, int y, int fill, int oldColor){
	if(getpixel(x,y) != fill){
		putpixel(x,y, fill);
		floodFill4(x+1, y, fill, oldColor);
		floodFill4(x-1, y, fill, oldColor);
		floodFill4(x, y+1, fill, oldColor);
		floodFill4(x, y-1, fill, oldColor);
	}
	getch();
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
	initgraph(&graphdriver, &graphmode, "..\\bgi");
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
	/*
	for (j=yS;j<=yF;j++){
		for(i=xS;i<=xF;i++){
			putpixel(i,j,BLACK);
		}
	} */
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
	getch();
	boundaryFillInteractive(pusat);	
}

void elipsInteractive(){
	int rh,rv,xc,yc;
	Point pusat;
	printf("Absis titik pusat ="); scanf("%d",&pusat.absis);
	printf("Ordinat titik pusat =");scanf("%d",&pusat.ordinat);
	printf("Jari-jari horizontal =");scanf("%d",&rh);
	printf("Jari-jari vertikal =");scanf("%d",&rv);

	pusat=getPixLoc(pusat);
	getch();

	initCanvas();
	ellipseMidpoint(pusat.absis, pusat.ordinat,rh,rv,GREEN);
	getch();
	boundaryFillInteractive(pusat);
}

void bezierCurve(int x[4], int y[4])
{
    int gd = DETECT, gm;
    int i;
    double t;

    for (t = 0.0; t < 1.0; t += 0.0005)
    {
	double xt = pow (1-t, 3) * x[0] + 3 * t * pow (1-t, 2) * x[1] +
		    3 * pow (t, 2) * (1-t) * x[2] + pow (t, 3) * x[3];

	double yt = pow (1-t, 3) * y[0] + 3 * t * pow (1-t, 2) * y[1] +
		    3 * pow (t, 2) * (1-t) * y[2] + pow (t, 3) * y[3];

	putpixel (xt, yt, GREEN);
	delay(1);
    }

    for (i=0; i<4; i++)
	putpixel (x[i], y[i], YELLOW);
}

void curveInteractive(){
    int x[4], y[4];
    Point P[4];
    int i;

    printf ("Masukkan 4 Buat titik kontrol\n");
    for (i=0; i<4; i++){
	printf("Abssis-i : ");scanf("%d", &P[i].absis);
	printf("Ordinat-i : ");scanf("%d", &P[i].ordinat);
	P[i] = getPixLoc(P[i]);
	x[i] = P[i].absis;
	y[i] = P[i].ordinat;
    }
    initCanvas();
    bezierCurve(x, y);
}

void boundaryFillInteractive(Point P){
	int ans;
	printf("Apakah akan Anda Arsir?[Y = 1/N = 0] : "); scanf("%d", &ans);
	if(ans){
		printf("MASUK %d %d", P.absis, P.ordinat);
		boundaryFill4Queue(P,YELLOW, GREEN);
	}
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
	getch();
	closegraph();
	return 0;
}
