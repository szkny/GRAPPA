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
#define LineNum 1000 /* Maximum Line Number of Free Hand */


class GRAPPA{
	private:
		double Cmargin; /* Margin of Canvas (%) */
		int WX,WY; /* Window Size */
		int Px[FreeMAX][LineNum],Py[FreeMAX][LineNum]; /* X,Y Coordinate */
		int Counter[LineNum],ID; /* Line Element Counter & Line ID */
		bool SFLAG; /* Status Flag */
		double LineColor[3][LineNum]; /* Line Color [0,1,2]=[R,G,B] */
		double LineWidth[LineNum]; /* Line Width */
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
	Cmargin = 2.0;
	WX = wx;
	WY = wy;
	for(int j=0;j<LineNum;++j){
		for(int i=0;i<FreeMAX;++i){
			Px[i][j] = 0;
			Py[i][j] = 0;
		}
		for(int i=0;i<3;++i){
			LineColor[i][j] = 0.0;
		}
		LineWidth[j] = 2.0;
		Counter[j] = 0;
	}
	ID = 0;
	SFLAG = true;
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
	LineColor[0][ID] = R;
	LineColor[1][ID] = G;
	LineColor[2][ID] = B;
}


void GRAPPA::DrawCanvas(){
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
	else{
		ID++;
		if(LineNum<ID) ID = 0;
	}
}


void GRAPPA::DrawFreeHand(){
	for(int j=0;j<=ID;++j){
		glPointSize(LineWidth[j]);
		glLineWidth(LineWidth[j]);
		glColor3d(LineColor[0][j],LineColor[1][j],LineColor[2][j]);
		if(Counter[j]==1){
			glBegin(GL_POINTS);
			glVertex2d((double)Px[0][j]/WX,1-(double)Py[0][j]/WY);
			glEnd();
		}
		else{
			glBegin(GL_LINE_STRIP);
			for(int i=0;i<Counter[j];++i){
				if((double)Px[i][j]<=(double)Cmargin/100*WX)
					glVertex2d((double)Cmargin/100,1-(double)Py[i][j]/WY);
				else if((double)(100-Cmargin)/100*WX<=(double)Px[i][j])
					glVertex2d(1.0-(double)Cmargin/100,1-(double)Py[i][j]/WY);
				else if((double)Py[i][j]<=(double)Cmargin/100*WY)
					glVertex2d((double)Px[i][j]/WX,1.0-(double)Cmargin/100);
				else if((double)(100-Cmargin)/100*WY<=(double)Py[i][j])
					glVertex2d((double)Px[i][j]/WX,(double)Cmargin/100);
				else
					glVertex2d((double)Px[i][j]/WX,1-(double)Py[i][j]/WY);
			}
			glEnd();
		}
	}
}


void GRAPPA::Display(){
	if(SFLAG){
		char s[50];
		int x = (Counter[ID]>1)? Px[Counter[ID]-1][ID]:0;
		int y = (Counter[ID]>1)? Py[Counter[ID]-1][ID]:0;
		sprintf(s,"[%d,%d]",x,y);
		glDrawString(s,0.03,0.95);
		sprintf(s,"Line No. %d Length %d",ID,Counter[ID]);
		glDrawString(s,0.03,0.92);
	}
}


void GRAPPA::Status(){
	if(SFLAG) SFLAG = false;
	else SFLAG = true;
}


/*****************************/

#endif //GRAPPA_h_
