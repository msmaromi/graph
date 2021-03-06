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
void boundaryFillInteractive(Point,int,int,int);
//------------------------------

int pembatas(int x, int y){
	if(x>10 && x<630 && y>10 && y<460){
		return 0;
	}else{
		return 1;
	}
}

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

void lineBRES(int x0,int y0,int x1,int y1,int color){
  int dx = abs (x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs (y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    putpixel(x0,y0,color);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}	

void lineFPA(int xa, int ya, int xb, int yb, int color){
	int dx = xb-xa;
	int dy = yb-ya;
	int x;
	float m = (dy/dx);
		
	for(x=xa;x<xb;x++){
	 	int y=m*x + ya;
		putpixel(x,y,YELLOW);
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
	if(!pembatas(xc+X, yc+Y))putpixel(xc+X, yc+Y, color);
	if(!pembatas(xc+X, yc-Y))putpixel(xc+X, yc-Y, color);
	if(!pembatas(xc-X, yc+Y))putpixel(xc-X, yc+Y, color);
	if(!pembatas(xc-X, yc-Y))putpixel(xc-X, yc-Y, color);
	if(!pembatas(xc+Y, yc+X))putpixel(xc+Y, yc+X, color);
	if(!pembatas(xc+Y, yc-X))putpixel(xc+Y, yc-X, color);
	if(!pembatas(xc-Y, yc+X))putpixel(xc-Y, yc+X, color);
	if(!pembatas(xc-Y, yc-X))putpixel(xc-Y, yc-X, color);
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

void boundaryFill4Queue(Point P, int fill, int boundary, int plus){
	int ListPointX[10000];
	int ListPointY[10000];
	int ListPointXBoundary[1000];
	int ListPointYBoundary[1000];
	int current,counter,counterBoundary;
	int currentW,currentE;
	Point W;
	Point E;
	Point PP;
	Point temp;
	counter = 0;
	counterBoundary =0;
	
	for(int i=0;i<10000;i++){
		ListPointX[i] = -2;
		ListPointY[i] = -3;
		if(i<1000){
			ListPointXBoundary[i] = -6;
			ListPointYBoundary[i] = -7;		
		}		
	}

	PP.absis = P.absis;
	PP.ordinat = P.ordinat;

	if(ListPointX[counter] == -2){
		current = getpixel(P.absis, P.ordinat);
		//printf("%d %d %d|", current, boundary, fill);
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
						if(pembatas(W.absis,W.ordinat))break;
						putpixel(W.absis,W.ordinat,fill);
						if(getpixel(W.absis, W.ordinat+1) != boundary && getpixel(W.absis, W.ordinat+1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat+1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}else if((getpixel(W.absis, W.ordinat+1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = W.absis;
							ListPointYBoundary[counterBoundary] = W.ordinat + 1;							
							counterBoundary++;
						}
						
						if(getpixel(W.absis, W.ordinat-1) != boundary && getpixel(W.absis , W.ordinat-1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat-1;
							ListPointX[j+1] =PP.absis;
							ListPointY[j+1]= PP.ordinat;
							j++;
						}else if((getpixel(W.absis, W.ordinat-1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = W.absis;
							ListPointYBoundary[counterBoundary] = W.ordinat - 1;							
							counterBoundary++;
						}

						W.absis ++; //geser kanan
						currentW = getpixel(W.absis, W.ordinat);				
						//getch();
					}
					
					if((currentW == boundary) && plus){
						ListPointXBoundary[counterBoundary] = W.absis;
						ListPointYBoundary[counterBoundary] = W.ordinat;							
						counterBoundary++;
					}					

					while(currentE != boundary && currentE != fill){
						if(pembatas(E.absis,E.ordinat))break;
						putpixel(E.absis,E.ordinat,fill);
						if(getpixel(E.absis, E.ordinat + 1) != boundary && getpixel(E.absis, E.ordinat + 1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat + 1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;	
							j++;
						}else if((getpixel(E.absis, E.ordinat+1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = E.absis;
							ListPointYBoundary[counterBoundary] = E.ordinat + 1;							
							counterBoundary++;
						}
						
						if(getpixel(E.absis , E.ordinat - 1) != boundary && getpixel(E.absis , E.ordinat -1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat-1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}else if((getpixel(E.absis, E.ordinat-1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = E.absis;
							ListPointYBoundary[counterBoundary] = E.ordinat - 1;							
							counterBoundary++;														
						}
						
						E.absis --; //geser kiri
						currentE = getpixel(E.absis, E.ordinat);
					}
					
					if((currentE == boundary) && plus){
						ListPointXBoundary[counterBoundary] = E.absis;
						ListPointYBoundary[counterBoundary] = E.ordinat;							
						counterBoundary++;
					}
					
				}else if((getpixel(temp.absis, temp.ordinat) == boundary) && plus){
						ListPointXBoundary[counterBoundary] = temp.absis;
						ListPointYBoundary[counterBoundary] = temp.ordinat;
						counterBoundary++;
				}
				counter++;
			}
		}
	}
	
	if(plus){
		i=0;
		while(1){
			if(ListPointXBoundary[i] > 0){
				putpixel(ListPointXBoundary[i],ListPointYBoundary[i],fill);
				i++;
			}else {
				break;
			}
		}
	}
}

void scanlineFill4(Point P, int fill, int boundary){
	int ListPointX[10000];
	int ListPointY[10000];
	int ListPointXBoundary[1000];
	int ListPointYBoundary[1000];
	int current,counter,counterBoundary;
	int currentW,currentE;
	int plus =0;
	Point W;
	Point E;
	Point PP;
	Point temp;
	counter = 0;
	counterBoundary =0;
	
	for(int i=0;i<10000;i++){
		ListPointX[i] = -2;
		ListPointY[i] = -3;
		if(i<1000){
			ListPointXBoundary[i] = -6;
			ListPointYBoundary[i] = -7;		
		}		
	}

	PP.absis = P.absis;
	PP.ordinat = P.ordinat;

	if(ListPointX[counter] == -2){
		current = getpixel(P.absis, P.ordinat);
		printf("%d %d %d|", current, boundary, fill);
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
					W.absis = temp.absis;
					//printf(" %d", W.absis);
					E.absis = temp.absis-1;
					W.ordinat = temp.ordinat;
					E.ordinat = temp.ordinat;
					currentW = getpixel(W.absis, W.ordinat);
					currentE = getpixel(E.absis, E.ordinat);					
					
					int j=counter;
				
					while(currentW != boundary && currentW != fill){
						if(!pembatas(W.absis,W.ordinat)){
							putpixel(W.absis,W.ordinat,fill);
						}
						if(getpixel(W.absis, W.ordinat+1) != boundary && getpixel(W.absis, W.ordinat+1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat+1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}else if((getpixel(W.absis, W.ordinat+1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = W.absis;
							ListPointYBoundary[counterBoundary] = W.ordinat + 1;							
							counterBoundary++;
						}
						
						if(getpixel(W.absis, W.ordinat-1) != boundary && getpixel(W.absis , W.ordinat-1) != fill){
							PP.absis = W.absis;
							PP.ordinat = W.ordinat-1;
							ListPointX[j+1] =PP.absis;
							ListPointY[j+1]= PP.ordinat;
							j++;
						}else if((getpixel(W.absis, W.ordinat-1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = W.absis;
							ListPointYBoundary[counterBoundary] = W.ordinat - 1;							
							counterBoundary++;
						}

						W.absis ++; //geser kanan
						currentW = getpixel(W.absis, W.ordinat);				
						//getch();
					}
					
					if((currentW == boundary) && plus){
						ListPointXBoundary[counterBoundary] = W.absis;
						ListPointYBoundary[counterBoundary] = W.ordinat;							
						counterBoundary++;
					}					

					while(currentE != boundary && currentE != fill){
						if(!pembatas(W.absis,W.ordinat)){
							putpixel(E.absis,E.ordinat,fill);
						}
						if(getpixel(E.absis, E.ordinat + 1) != boundary && getpixel(E.absis, E.ordinat + 1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat + 1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;	
							j++;
						}else if((getpixel(E.absis, E.ordinat+1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = E.absis;
							ListPointYBoundary[counterBoundary] = E.ordinat + 1;							
							counterBoundary++;
						}
						
						if(getpixel(E.absis , E.ordinat - 1) != boundary && getpixel(E.absis , E.ordinat -1) != fill){
							PP.absis = E.absis;
							PP.ordinat = E.ordinat-1;
							ListPointX[j+1] = PP.absis;
							ListPointY[j+1] = PP.ordinat;
							j++;
						}else if((getpixel(E.absis, E.ordinat-1) == boundary) && plus){
							ListPointXBoundary[counterBoundary] = E.absis;
							ListPointYBoundary[counterBoundary] = E.ordinat - 1;							
							counterBoundary++;														
						}
						
						E.absis --; //geser kiri
						currentE = getpixel(E.absis, E.ordinat);
					}
					
					if((currentE == boundary) && plus){
						ListPointXBoundary[counterBoundary] = E.absis;
						ListPointYBoundary[counterBoundary] = E.ordinat;							
						counterBoundary++;
					}
					
				}else if((getpixel(temp.absis, temp.ordinat) == boundary) && plus){
						ListPointXBoundary[counterBoundary] = temp.absis;
						ListPointYBoundary[counterBoundary] = temp.ordinat;
						counterBoundary++;
				}
				counter++;
			}
		}
	}
	
	if(plus){
		i=0;
		while(1){
			if(ListPointXBoundary[i] > 0){
				putpixel(ListPointXBoundary[i],ListPointYBoundary[i],fill);
				i++;
			}else {
				break;
			}
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

void translation(int a, int b){
	Point pusat, akhir, draw;
	pusat.absis = 0;
	pusat.ordinat = 0;
	pusat=getPixLoc(pusat);	
	
	akhir.absis= a;
	akhir.ordinat = b;

	circleBRES(pusat,10,GREEN);
		
	int xa,xb,ya,yb;
	//--------------
	xa= pusat.absis;
	xb= akhir.absis;
	ya= pusat.ordinat;
	yb= akhir.ordinat;
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

	draw.absis=ROUND(x);
	draw.ordinat = ROUND(y);
	if(pembatas(draw.absis,draw.ordinat)){

	}
	circleBRES(draw,100,GREEN);			
	for(k=0; k<steps;k++){
		delay(20);
		circleBRES(draw,100,BLACK);					
		x+=xIncrement;
		y+=yIncrement;
		draw.absis=ROUND(x);
		draw.ordinat = ROUND(y);
		if(pembatas(draw.absis,draw.ordinat)){
			break;
		}
		circleBRES(draw,100,GREEN);		
	}
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
	boundaryFill4Queue(pusKor, RED,RED,0);
}

void translationInteractive(){
	Point P1;
	
	printf("Akan dilakukan penggerakan object (lingkaran) dari titik (0,0) ketitik tujuan\n");
	printf("Absis Pakhir =");
	scanf("%d",&P1.absis);
	printf("Ordinat Pakhir =");
	scanf("%d",&P1.ordinat);
	
	P1=getPixLoc(P1);

	printf("\nAnda dilakukan translasi dari titik (0,0) ke titik tujua");
	printf("\nPRESS ANY KEY TO CONTINUE...");
	getch();
	initCanvas();
	translation(P1.absis, P1.ordinat);
		
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
	printf("3. FPA\n");
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
	}else if(algo ==3){
		printf("\nAnda akan menggambar garis dengan algoritma");
		printf(" FPA \nPRESS ANY KEY TO CONTINUE...");
		getch();
		initCanvas();
		lineFPA(P1.absis,P1.ordinat,P2.absis,P2.ordinat,GREEN);
	}else{
		printf("Masukan Salah, program akan keluar");
	}
	getch();
}

void circleInteractive(){
	Point pusat;
	int r;
	int plus;
	int scanline;
	printf("Absis titik pusat ="); scanf("%d",&pusat.absis);
	printf("Ordinat titik pusat ="); scanf("%d",&pusat.ordinat);
	printf("Masukkan jari-jari lingkaran ="); scanf("%d",&r); 
	printf("Berikut Algoritma Filling yang mampu digunakan :");
	printf("\n 1.BoundaryFill");
	printf("\n 2.FloodFill");
	printf("\n 3.ScanlineFil;");
	printf("\n Masukkan Pilihan Anda : ");  scanf("%d", &scanline);
	if(scanline ==2 || scanline == 1){
		if(scanline ==2) plus =1;
		if(scanline ==1) plus =0;
		initCanvas();
		pusat=getPixLoc(pusat);
		circleBRES(pusat,r,GREEN);
		getch();
		boundaryFillInteractive(pusat, YELLOW, GREEN, plus);
	}else if(scanline ==3){
		initCanvas();
		pusat=getPixLoc(pusat);
		circleBRES(pusat,r,GREEN);
		getch();
		pusat.absis -= r-1;
		scanlineFill4(pusat, YELLOW, GREEN);
	}

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
	boundaryFillInteractive(pusat, YELLOW, GREEN, 0);
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

void boundaryFillInteractive(Point P, int Fill, int Boundary,int plus){
	int ans;
	printf("Apakah akan Anda Arsir?[Y = 1/N = 0] : "); scanf("%d", &ans);
	if(ans){
		//printf("MASUK %d %d", P.absis, P.ordinat);
		boundaryFill4Queue(P,Fill, Boundary, plus);
	}
}

void trapesiumInteractive(){
	Point P1,P2,P3,P4;
	P1.absis = 20;
	P1.ordinat = 20;
	P2.absis = 50;
	P2.ordinat =50;
	P3.absis = 100;
	P3.ordinat = 50;
	P4.absis = 150;
	P4.ordinat = 20;

	P1 = getPixLoc(P1);
	P2 = getPixLoc(P2);
	P3 = getPixLoc(P3);
	P4 = getPixLoc(P4);

	initCanvas();

	lineDDA(P1, P2, GREEN);
	lineDDA(P2, P3, GREEN);
	lineDDA(P3, P4, GREEN);
	lineDDA(P4, P1, GREEN);

	getch();
	Point P;
	P.absis = 100;
	P.ordinat = 40;
	P = getPixLoc(P);
	boundaryFillInteractive(P, GREEN, GREEN, 0);
	getch();
	boundaryFillInteractive(P, BLUE, GREEN, 0);
	getch();
}

void clippingInteractive(){
	Point Center;
	Center.absis = 75;
	Center.ordinat = 85;
	Center = getPixLoc(Center);
	int r = 10;
	int fill = YELLOW;
	
	initCanvas();			
	sleep(1);
	circleBRES(Center, r, GREEN);
	boundaryFill4Queue(Center, fill, GREEN, 0);
	getch();
	printf("tes kbhit() [%d %d]:", Center.absis, Center.ordinat);
	char key;
	int increment=5;
	while(1){	
		if (kbhit()){
	 		key=getch();
	 		switch (key){
	 			case 'i':
	 				//printf("i ");
					boundaryFill4Queue(Center, BLACK, GREEN, 0);
 					circleBRES(Center, r, BLACK);	 
// 						if(x>10 && x<630 && y>10 && y<460){					 				
 					if((Center.ordinat) > (10-r))Center.ordinat -=increment;
 					circleBRES(Center, r, GREEN);	 			
 					boundaryFill4Queue(Center, YELLOW, GREEN, 0); 						 					
	 				break;
	 			case 'j':
	 				//printf("j ");
					boundaryFill4Queue(Center, BLACK, GREEN, 0);	 				
 					circleBRES(Center, r, BLACK);	 					 				
 					if((Center.absis) > (10-r))Center.absis -=increment;	 				
					circleBRES(Center, r, GREEN);
 					boundaryFill4Queue(Center, YELLOW, GREEN, 0);	
	 				break;
	 			case 'k':
	 				//printf("k ");
					boundaryFill4Queue(Center, BLACK, GREEN, 0);	 				
 					circleBRES(Center, r, BLACK);	 					 				
					if((Center.ordinat) < (460+r))Center.ordinat +=increment;			 				
	 				circleBRES(Center, r, GREEN);	 			
 					boundaryFill4Queue(Center, YELLOW, GREEN, 0);		
	 				break;
	 			case 'l':
	 				//printf("l ");
					boundaryFill4Queue(Center, BLACK, GREEN, 0);
 					circleBRES(Center, r, BLACK);	 					 	
					if((Center.absis) < (630+r))Center.absis +=increment;					 				
	 				circleBRES(Center, r, GREEN);	 			
 					boundaryFill4Queue(Center, YELLOW, GREEN, 0);	 					
	 				break;
	 			case 'x':
	 				printf("EXIT ");
	 				break;	 			
	 		}
	 		if(key == 'x') break;
		}    
	}
	printf("%d %d", Center.absis, Center.ordinat);
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
	printf("5. Translation\n");
	printf("6. Clipping\n");
	
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
		case 5:
			translationInteractive();
			break;			
		case 6:
			clippingInteractive();
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

