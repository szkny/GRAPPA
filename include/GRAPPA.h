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
#define CmdNum 100  /* Number of Stored Command */


class GRAPPA{
	private:
		double Cmargin; /* Margin of Canvas (%) */
		int WX,WY; /* Window Size */
		int Px[FreeMAX][LineNum],Py[FreeMAX][LineNum]; /* X,Y Coordinate */
		int Counter[LineNum],ID; /* Line Element Counter & Line ID */
		bool SFLAG; /* Status Flag */
		bool CFLAG; /* Command Line Flag */
		double LineColor[3][LineNum]; /* Line Color [0,1,2]=[R,G,B] */
		double LineWidth[LineNum]; /* Line Width */
		char CommandString[CmdNum][64]; /* Input Command String */
		int CmdID; /* Command ID */
		int HstCounter; /* Go Back Counter for CommandHistory */
	public:
		GRAPPA();
		inline void Init(int WX, int XY);
		inline void NewFreeHand();
		inline void Undo();
		inline void SetColor(double R, double G, double B);
		inline void DrawCanvas();
		inline void SetCoordinate(int x, int y);
		inline void DrawFreeHand();
		inline void Display();
		inline void Status();
		inline void CommandMode();
		inline bool CommandFlag();
		inline int CommandStore(unsigned char key);
		inline int CommandHistory(int key);
		inline bool RunCommand(const char *s0);
		inline bool RunCommand(const char *s0, const char *s1);
		inline bool RunCommand(const char *s0, const char *s1, const char *s2);
};


inline GRAPPA::GRAPPA(){
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
	}	ID = 0;
	SFLAG = true;
	CmdID = 0;
	HstCounter = 0;
}


inline void GRAPPA::Init(int wx, int wy){
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
	CmdID = 0;
}


inline void GRAPPA::NewFreeHand(){
	ID++;
	if(LineNum<ID) ID = 0;
}


inline void GRAPPA::Undo(){
	Counter[ID] = 0;
	if(0<ID) ID--;
}


inline void GRAPPA::SetColor(double R, double G, double B){
	LineColor[0][ID] = R;
	LineColor[1][ID] = G;
	LineColor[2][ID] = B;
}


inline void GRAPPA::DrawCanvas(){
	glColor3d(1.0,1.0,1.0);
	glBegin(GL_QUADS);
	glVertex2d(Cmargin/100,Cmargin/100);
	glVertex2d((100-Cmargin)/100,Cmargin/100);
	glVertex2d((100-Cmargin)/100,(100-Cmargin)/100);
	glVertex2d(Cmargin/100,(100-Cmargin)/100);
	glEnd();
}


inline void GRAPPA::SetCoordinate(int x, int y){
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


inline void GRAPPA::DrawFreeHand(){
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


inline void GRAPPA::Display(){
	if(SFLAG){
		char s[128];
		int x = (Counter[ID]>1)? Px[Counter[ID]-1][ID]:0;
		int y = (Counter[ID]>1)? Py[Counter[ID]-1][ID]:0;
		sprintf(s,"[%d,%d]",x,y);
		glDrawString(s,0.03,0.95);
		sprintf(s,"Line No. %d Length %d",ID,Counter[ID]);
		glDrawString(s,0.03,0.92);
	}
	if(CFLAG){
		char s[128];
		sprintf(s,":%s",CommandString[CmdID]);
		glDrawString(s,0.03,0.05);
	}
}


inline void GRAPPA::Status(){
	if(SFLAG) SFLAG = false;
	else SFLAG = true;
}


inline void GRAPPA::CommandMode(){
	if(CFLAG) CFLAG = false;
	else CFLAG = true;
}


inline bool GRAPPA::CommandFlag(){
	return CFLAG;
}


inline int GRAPPA::CommandStore(unsigned char key){
	int size = strlen(CommandString[CmdID]);
	if(CFLAG){
		if(key == 127){ //delete key
			if(0<size)
				memset(CommandString[CmdID]+size-1,'\0',1);
			else{ 
				HstCounter = 0;
				CFLAG = false;
			}	
		}
		else if(key == 13){ //return key
			if(0<size){
				if(HstCounter) HstCounter = 0;
				if(CmdID<CmdNum) ++CmdID;
				else CmdID = 0;
				CFLAG = false;
			}
		}
		else{
			char s[4];
			sprintf(s,"%c",key);
			if(size<32) strcat(CommandString[CmdID],s);
		}
	}
	return size;
}


inline int GRAPPA::CommandHistory(int key){
	if(CFLAG){
		switch(key){
			case GLUT_KEY_UP://up-arrow key
				if(0<CmdID-HstCounter){
					if(strlen(CommandString[CmdID-HstCounter-1])){
						++HstCounter;
						strcpy(CommandString[CmdID],CommandString[CmdID-HstCounter]);
					}
				}
				break;
			case GLUT_KEY_DOWN://down-arrow key
				if(CmdID-HstCounter<CmdNum-1){
					if(strlen(CommandString[CmdID-HstCounter+1])){
						if(0<HstCounter) --HstCounter;
						strcpy(CommandString[CmdID],CommandString[CmdID-HstCounter]);
					}
					if(HstCounter==0)
						memset(CommandString[CmdID],'\0',sizeof(CommandString[CmdID]));
				}
				break;
			default:
				break;
		}
	}
	return strlen(CommandString[CmdID]);
}


inline bool GRAPPA::RunCommand(const char *s0){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, const char *s1){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	if(!strcmp(CommandString[CmdID],s1)) match = true;
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, const char *s1, const char *s2){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	if(!strcmp(CommandString[CmdID],s1)) match = true;
	if(!strcmp(CommandString[CmdID],s2)) match = true;
	return match;
}


/*****************************/

#endif //GRAPPA_h_
