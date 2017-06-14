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
#define CmdNum  1000 /* Number of Stored Command */

/* for draw pixel mode */
#define Xpixel 200
#define Ypixel 125

class GRAPPA{
	private:
		double Cmargin; /* Margin of Canvas (%) */
		int    WX,WY;   /* Window Size */
		double CanvasColor[3]; /* Canvas Color R,G,B */
		int    Px[FreeMAX][LineNum]; /* X Coordinate */ 
		int    Py[FreeMAX][LineNum]; /* Y Coordinate */
		int    Counter[LineNum];     /* Line Element Counter */
		int    TmpCount[LineNum];    /* Temporary Line Element Counter */
		int    LineID; /* Line ID */
		int    TmpID;  /* Temporary Line ID */
		bool   PFLAG;  /* Pixel Mode Flag */
		bool   SFLAG;  /* Status Flag */
		bool   CFLAG;  /* Command Line Flag */
		double LineColor[3][LineNum]; /* Line Color [0,1,2]=[R,G,B] */
		double LineWidth[LineNum];    /* Line Width */
		char   CommandString[CmdNum][64]; /* Input Command String */
		int    CmdID;      /* Command LineID */
		int    CmdCursor;  /* Command Cursor */
		int    HstCounter; /* Go Back Counter for CommandHistory */
		double Pixel[3][Xpixel][Ypixel]; /* [RGB][X][Y] */
		int    PixelSize; /* Size of Pixel */
	public:
		GRAPPA();
		inline void Init(int WX, int XY);
		inline void Reset();
		inline void NewFreeHand();
		inline void Undo();
		inline void Redo();
		inline void EraseLine();
		inline void SetCanvasColor(double R, double G, double B);
		inline void SetLineColor(double R, double G, double B);
		inline void SetDefaultLineColor(double R, double G, double B);
		inline void SetLineWidth(double w);
		inline void SetDefaultLineWidth(double w);
		inline void SetPixelSize(int size);
		inline void SetCoordinate(int x, int y);
		inline void DrawCanvas();
		inline void DrawFreeHand();
		inline bool PixelFlag();
		inline void PixelMode();
		inline void FillPixel();
		inline void DrawPixel();
		inline void Display();
		inline void Status();
		inline void SetLineID(int ID);
		inline void BackLineID();
		inline void CommandMode();
		inline bool CommandFlag();
		inline int  CommandStore(unsigned char key);
		inline int  CommandHistory(int key);
		inline void CommandCursor(int key);
		inline bool RunCommand(const char *s0);
		inline bool RunCommand(const char *s0, const char *s1);
		inline bool RunCommand(const char *s0, const char *s1, const char *s2);
		inline bool RunCommand(const char *s0, double *a1);
		inline bool RunCommand(const char *s0, double *a1, double *a2);
		inline bool RunCommand(const char *s0, double *a1, double *a2, double *a3);
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
		Counter[j]   = 0;
		TmpCount[j]  = 0;
	}
	for(int i=0;i<3;++i){
		CanvasColor[i] = 1.0;
		for(int j=0;j<Xpixel;++j)
			for(int k=0;k<Ypixel;++k)
				Pixel[i][j][k] = 1.0;
	}
	LineID = 0;
	TmpID  = 0;
	PFLAG  = false;
	SFLAG  = true;
	CFLAG  = false;
	CmdID  = 0;
	CmdCursor  = 0;
	HstCounter = 0;
	PixelSize  = 1;
}


inline void GRAPPA::Init(int wx, int wy){
	/* configuration of anti-aliasing */
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/* setting of canvas */
	Cmargin = 0.0;
	WX = wx;
	WY = wy;
}


inline void GRAPPA::Reset(){
	for(int j=0;j<LineNum;++j){
		for(int i=0;i<FreeMAX;++i){
			Px[i][j] = 0;
			Py[i][j] = 0;
		}
		for(int i=0;i<3;++i){
			LineColor[i][j] = 0.0;
		}
		LineWidth[j] = 2.0;
		Counter[j]   = 0;
		TmpCount[j]  = 0;
	}
	for(int i=0;i<3;++i){
		CanvasColor[i] = 1.0;
		for(int j=0;j<Xpixel;++j)
			for(int k=0;k<Ypixel;++k)
				Pixel[i][j][k] = 1.0;
	}
	LineID = 0;
	TmpID  = 0;
}


inline void GRAPPA::NewFreeHand(){
	if(!TmpID){
		LineID++;
		if(LineNum<LineID) LineID = 0;
		Counter[LineID] = 0;
	}
}


inline void GRAPPA::Undo(){
	TmpCount[LineID] = Counter[LineID];
	Counter[LineID] = 0;
	if(0<LineID) --LineID;
}


inline void GRAPPA::Redo(){
	if(LineID+1<LineNum){
		if(Px[0][LineID+1] && Py[0][LineID+1]){
			++LineID;
			Counter[LineID] = TmpCount[LineID];
		}
	}
}


inline void GRAPPA::EraseLine(){
	if(Counter[LineID]) --Counter[LineID];
	else if(LineID) --LineID;
}


inline void GRAPPA::SetCanvasColor(double R, double G, double B){
	for(int j=0;j<Ypixel;++j){
		for(int i=0;i<Xpixel;++i){
			if(Pixel[0][i][j]==CanvasColor[0]){
				if(Pixel[1][i][j]==CanvasColor[1]){
					if(Pixel[2][i][j]==CanvasColor[2]){
						Pixel[0][i][j] = R;
						Pixel[1][i][j] = G;
						Pixel[2][i][j] = B;
					}
				}
			}
		}
	}
	CanvasColor[0] = R;
	CanvasColor[1] = G;
	CanvasColor[2] = B;
	SetDefaultLineColor(1.0-R,1.0-G,1.0-B);
}

inline void GRAPPA::SetLineColor(double R, double G, double B){
	LineColor[0][LineID] = R;
	LineColor[1][LineID] = G;
	LineColor[2][LineID] = B;
}


inline void GRAPPA::SetDefaultLineColor(double R, double G, double B){
	for(int i=LineID+1;i<LineNum;++i){
		LineColor[0][i] = R;
		LineColor[1][i] = G;
		LineColor[2][i] = B;
	}
}


inline void GRAPPA::SetLineWidth(double w){
	if(5.0<w) w = 5.0;
	LineWidth[LineID] = w;
}


inline void GRAPPA::SetDefaultLineWidth(double w){
	SetPixelSize((int)w);
	if(5.0<w) w = 5.0;
	for(int i=LineID+1;i<LineNum;++i){
		LineWidth[i] = w;
	}
}


inline void GRAPPA::SetPixelSize(int size){
	const int max = 30;
	if(1<size && size<max) PixelSize = size;
	else if(max<=size)     PixelSize = max;
	else                   PixelSize = 1;
}


inline void GRAPPA::SetCoordinate(int x, int y){
	if(!TmpID){
		if(Counter[LineID]<FreeMAX){
			Px[Counter[LineID]][LineID] = x;
			Py[Counter[LineID]][LineID] = y;
			Counter[LineID]++;
		}
		else{
			LineID++;
			if(LineNum<LineID) LineID = 0;
		}
		FillPixel();
	}
}


inline void GRAPPA::DrawCanvas(){
	if(!PFLAG){
		glColor3d(CanvasColor[0],CanvasColor[1],CanvasColor[2]);
		glBegin(GL_QUADS);
		glVertex2d(Cmargin/100,Cmargin/100);
		glVertex2d((100-Cmargin)/100,Cmargin/100);
		glVertex2d((100-Cmargin)/100,(100-Cmargin)/100);
		glVertex2d(Cmargin/100,(100-Cmargin)/100);
		glEnd();
	}
}


inline void GRAPPA::DrawFreeHand(){
	if(!PFLAG){
		for(int j=0;j<=LineID;++j){
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
}


inline bool GRAPPA::PixelFlag(){
	return PFLAG;
}


inline void GRAPPA::PixelMode(){
	if(PFLAG) PFLAG = false;
	else      PFLAG = true;
}



#define PixelBlottingOut(x,y){\
	for(int k=1;k<=PixelSize;++k){\
		int jmax = k*k;\
		for(int j=0;j<jmax;++j){\
			double xi = x+k*cos(2*PI*j/jmax);\
			double yi = y+k*sin(2*PI*j/jmax);\
			int chx = (int)((double)Xpixel*xi/WX);\
			int chy = (int)((double)Ypixel*yi/WY);\
			if(0<chx&&chx<Xpixel && 0<chy&&chy<Ypixel)\
				for(int i=0;i<3;++i)\
					Pixel[i][chx][chy] = LineColor[i][LineID];\
		}\
	}\
}
inline void GRAPPA::FillPixel(){
	int c = Counter[LineID]-1;
	if(0<c){
		double vx = Px[c][LineID]-Px[c-1][LineID];
		double vy = Py[c][LineID]-Py[c-1][LineID];
		double v  = sqrt(vx*vx+vy*vy);
		if(v!=0.0){
			vx /= v;
			vy /= v;
			double x0 = Px[c-1][LineID];
			double y0 = Py[c-1][LineID];
			double px = x0;
			double py = y0;
			double distance = 0.0;
			int whilecount = 0;
			int whilemax   = 1e6;
			while(distance<v){
				px += vx;
				py += vy;
				distance = sqrt(pow(x0-px,2)+pow(y0-py,2));
				PixelBlottingOut(px,py);
				++whilecount;
				if(whilemax<whilecount) break;
			}
		}
		else{
			PixelBlottingOut(Px[c][LineID],Py[c][LineID]);
		}
	}
	else{ //c<=0
		PixelBlottingOut(Px[0][LineID],Py[0][LineID]);
	}
}
#undef PixelBlottingOut


inline void GRAPPA::DrawPixel(){
	if(PFLAG){
		glBegin(GL_QUADS);
		for(int j=0;j<Ypixel;++j){
			for(int i=0;i<Xpixel;++i){
				glColor3d(Pixel[0][i][j],Pixel[1][i][j],Pixel[2][i][j]);
				glVertex2d((i  )/((double)Xpixel),(Ypixel-j-1)/((double)Ypixel));
				glVertex2d((i+1)/((double)Xpixel),(Ypixel-j-1)/((double)Ypixel));
				glVertex2d((i+1)/((double)Xpixel),(Ypixel-j  )/((double)Ypixel));
				glVertex2d((i  )/((double)Xpixel),(Ypixel-j  )/((double)Ypixel));
			}
		}
		glEnd();
	}
}


inline void GRAPPA::Display(){
	glColor3d(1.0-CanvasColor[0],1.0-CanvasColor[1],1.0-CanvasColor[2]);
	char s[128];
	if(SFLAG){
		int x = (Counter[LineID]>1)? Px[Counter[LineID]-1][LineID]:0;
		int y = (Counter[LineID]>1)? Py[Counter[LineID]-1][LineID]:0;
		sprintf(s,"[%d,%d]",x,y);
		glDrawString(s,(Cmargin+1)/100,(100-Cmargin-3)/100);
		sprintf(s,"Line No. %d Length %d",LineID,Counter[LineID]);
		glDrawString(s,(Cmargin+1)/100,(100-Cmargin-6)/100);
	}
	if(CFLAG){
		static unsigned char count = 0;
		static bool flag = false;
		if(flag){
			sprintf(s,":%s",CommandString[CmdID]);
			if(count%32==0) flag = false; 
		}
		else{
			memset(s,'\0',sizeof(s));
			sprintf(s,":%s",CommandString[CmdID]);
			int size = strlen(s);
			memset(s+size-CmdCursor,'|',1);
			if(count%32==0) flag = true;
		}
		++count;
		glDrawString(s,(Cmargin+1)/100,(Cmargin+2)/100);
	}
}


inline void GRAPPA::SetLineID(int ID){
	if(!TmpID && 0<ID && ID<LineID){
		TmpID  = LineID;
		LineID = ID;
	}
}


inline void GRAPPA::BackLineID(){
	if(TmpID){
		LineID = TmpID;
		TmpID  = 0;
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
		if(key == 127){//delete key
			if(0<size)
				if(CmdCursor){
					if(CmdCursor<size){
						for(int i=size-CmdCursor;i<size;++i){
							CommandString[CmdID][i-1] = CommandString[CmdID][i];
						}
						CommandString[CmdID][size-1] = '\0';
					}
				}
				else memset(CommandString[CmdID]+size-1,'\0',1);
			else{ 
				HstCounter = 0;
				CFLAG = false;
			}	
		}
		else if(key == 13){//return key
			if(0<size){
				if(HstCounter) HstCounter = 0;
				if(CmdCursor)  CmdCursor  = 0;
				++CmdID;
				if(CmdNum<=CmdID){
					CmdID = 0;
					memset(CommandString[CmdID],'\0',sizeof(CommandString[CmdID]));
				}
				CFLAG = false;
			}
		}
		else{
			if(CmdCursor){
				char tmp[128];
				for(int i=0;i<CmdCursor;++i)
					tmp[i] = CommandString[CmdID][i+size-CmdCursor];
				memset(CommandString[CmdID]+size-CmdCursor,key,1);
				memset(CommandString[CmdID]+size-CmdCursor+1,'\0',1);
				if(size<32) sprintf(CommandString[CmdID],"%s%s",CommandString[CmdID],tmp);
			}
			else{
				char s[4];
				sprintf(s,"%c",key);
				if(size<32) strcat(CommandString[CmdID],s);
			}
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


inline void GRAPPA::CommandCursor(int key){
	if(CFLAG){
		switch(key){
			case GLUT_KEY_RIGHT://right-arrow key
				--CmdCursor;
				if(CmdCursor<0) CmdCursor = 0;
				break;
			case GLUT_KEY_LEFT://left-arrow key
				++CmdCursor;
				if((int)strlen(CommandString[CmdID])<CmdCursor)
					CmdCursor = strlen(CommandString[CmdID])-1;
				break;
			default:
				break;
		}
	}
}


inline bool GRAPPA::RunCommand(const char *s0){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	if(match) printf("Command:%s\n",CommandString[CmdID]);
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, const char *s1){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	if(!strcmp(CommandString[CmdID],s1)) match = true;
	if(match) printf("Command:%s\n",CommandString[CmdID]);
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, const char *s1, const char *s2){
	bool match = false;
	if(!strcmp(CommandString[CmdID],s0)) match = true;
	if(!strcmp(CommandString[CmdID],s1)) match = true;
	if(!strcmp(CommandString[CmdID],s2)) match = true;
	if(match) printf("Command:%s\n",CommandString[CmdID]);
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, double *a1){
	bool match = false;
	char Command[64];
	double arg1 = 0.0;
	sscanf(CommandString[CmdID],"%s %lf",Command,&arg1);
	if(!strcmp(Command,s0)) match = true;
	if(match){
		(*a1) = arg1;
		printf("Command:%s\t%f\n",Command,(*a1));
	}
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, double *a1, double *a2){
	bool match = false;
	char Command[64];
	double arg1 = 0.0;
	double arg2 = 0.0;
	sscanf(CommandString[CmdID],"%s %lf %lf",Command,&arg1,&arg2);
	if(!strcmp(Command,s0)) match = true;
	if(match){
		(*a1) = arg1;
		(*a2) = arg2;
		printf("Command:%s\t%f\t%f\n",Command,(*a1),(*a2));
	}
	return match;
}


inline bool GRAPPA::RunCommand(const char *s0, double *a1, double *a2, double *a3){
	bool match = false;
	char Command[64];
	double arg1 = 0.0;
	double arg2 = 0.0;
	double arg3 = 0.0;
	sscanf(CommandString[CmdID],"%s %lf %lf %lf",Command,&arg1,&arg2,&arg3);
	if(!strcmp(Command,s0)) match = true;
	if(match){
		(*a1) = arg1;
		(*a2) = arg2;
		(*a3) = arg3;
		printf("Command:%s\t%f\t%f\t%f\n",Command,(*a1),(*a2),(*a3));
	}
	return match;
}


/*****************************/

#endif //GRAPPA_h_
