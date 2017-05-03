#ifndef GRAPPA_h_
#define GRAPPA_h_

/*****************************/

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#include<GL/glut.h>
#include<MyGLUT.h>

#define FreeMAX 1000 /* Element of Free Hand */
#define LineNum 100  /* Maximum Line Number of Free Hand */


class GRAPPA{
	private:
		int WX,WY; /* Window Size */
		int Px[FreeMAX][LineNum],Py[FreeMAX][LineNum]; /* X,Y Coordinate */
		int Counter[LineNum],ID; /* Element Counter & Line Number ID */
		bool SFLAG; /* Status Flag */
	public:
		void Init(int WX, int XY);
		void NewFreeHand();
		void Undo();
		void SetColor(double R, double G, double B);
		void DrawCanvas();
		void SetCoordinate(int x, int y);
		void DrawFreeHand();
		void Display();
		void Status();
};


void GRAPPA::Init(int wx, int wy){
	WX = wx;
	WY = wy;
	for(int j=0;j<LineNum;++j){
		for(int i=0;i<FreeMAX;++i){
			Px[i][j] = 0;
			Py[i][j] = 0;
		}
		Counter[j] = 0;
	}
	ID = 0;
	SFLAG = false;
}


void GRAPPA::NewFreeHand(){
	ID++;
	if(LineNum<ID) ID = 0;
}


void GRAPPA::Undo(){
	Counter[ID] = 0;
	if(0<ID) ID--;
}


void GRAPPA::SetColor(double R, double G, double B){
	glColor3d(R,G,B);
}


void GRAPPA::DrawCanvas(){
	double Cmargin = 2.0;
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glVertex2d(Cmargin/100,Cmargin/100);
	glVertex2d((100-Cmargin)/100,Cmargin/100);
	glVertex2d((100-Cmargin)/100,(100-Cmargin)/100);
	glVertex2d(Cmargin/100,(100-Cmargin)/100);
	glEnd();
}


void GRAPPA::SetCoordinate(int x, int y){
	if(Counter[ID]<FreeMAX){
		Px[Counter[ID]][ID] = x;
		Py[Counter[ID]][ID] = y;
		Counter[ID]++;
	}
	else Counter[ID] = 0;
}


void GRAPPA::DrawFreeHand(){
	for(int j=0;j<=ID;++j){
		glBegin(GL_LINE_STRIP);
		for(int i=0;i<Counter[j];++i){
			glVertex2d((double)Px[i][j]/WX,1-(double)Py[i][j]/WY);
		}
		glEnd();
	}
}


void GRAPPA::Display(){
	if(SFLAG){
		char s[50];
		int x = (Counter[ID]>1)? Px[Counter[ID]-1][ID]:0;
		int y = (Counter[ID]>1)? Py[Counter[ID]-1][ID]:0;
		sprintf(s,"[%d,%d]",x,y);
		glDrawString(s,0.03,0.95);
		sprintf(s,"No. %d",ID);
		glDrawString(s,0.03,0.92);
	}
}


void GRAPPA::Status(){
	if(SFLAG) SFLAG = false;
	else SFLAG = true;
}


/*****************************/

#endif //GRAPPA_h_
