#ifndef GRAPPA_h_
#define GRAPPA_h_

/*****************************/

#ifdef __APPLE__
#include<GLUT/glut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<MyGLUT.h>
#include<Colors.h>

#define FreeMAX 1000 /* Element of Free Hand */
#define LineNum 1000 /* Maximum Line Number of Free Hand */

/* for Draw Pixel Mode */
#define Xpixel 200
#define Ypixel 125

/* Mouse Mode */
#define MFREEHAND       0
#define MCOLORBARLINE   1
#define MCOLORBARCANVAS 2
#define MCIRCLE         3
#define MSQUARE         4
#define MPOLYGON        5
#define MSTRAIGHTLINE   6
#define MRANDOM         7
#define MKALEIDO        8
#define MLINEMOVE       9
#define MLINECOPY       10
#define MLINEROTATE     11

/* Circle Samples */
#define CircleSample 50

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
		int    DrawMode; /* Draw Mode */
		int    Nside;  /* for draw N-side Polygon */
		bool   TmpFlag;/* Temporary Flag */
		bool   PXFLAG; /* Pixel Mode Flag */
		bool   ERFLAG; /* Eraser Flag */
		bool   STFLAG; /* Status Flag */
		const int ColorBarArray; /* Number of Color Bar Array */
		double *ColorBarWidth;   /* Width of Color Bar */
		double LineColor[3][LineNum]; /* Line Color [0,1,2]=[R,G,B] */
		double LineWidth[LineNum];    /* Line Width */
		double Pixel[3][Xpixel][Ypixel]; /* [RGB][X][Y] */
		double TmpPixel[3][Xpixel][Ypixel]; /* [RGB][X][Y] */
		int    PixelSize; /* Size of Pixel */
		int    PixelEraserCounter; /* Counter of Pixel Eraser */
	public:
		GRAPPA();
		~GRAPPA();
		inline void Init(int WX, int XY);
		inline void Reset();
		inline void NewFreeHand();
		inline void Undo();
		inline void Redo();
		inline void EraseLine();
		inline void DrawColorBar();
		inline void SetCanvasColor(double R, double G, double B);
		inline void SetLineColor(double R, double G, double B);
		inline void SetDefaultLineColor(double R, double G, double B);
		inline void SetLineWidth(double w);
		inline void SetDefaultLineWidth(double w);
		inline void SetPixelSize(int size);
		inline int  CurrentDrawMode();
		inline void SetDrawMode(int mode);
		inline void SetDrawMode(int mode,int N_side);
		inline void SetCoordinate(int x, int y);
		inline void SetLineCircle(int x, int y);
		inline void SetLineSquare(int x, int y);
		inline void SetLinePolygon(int x, int y);
		inline void SetStraightLine(int x, int y);
		inline void SetRandom(int x, int y);
		inline void SetKaleido(int x, int y);
		inline void LineMove(int x, int y);
		inline void LineCopy(int x, int y);
		inline void LineRotate(int x, int y);
		inline void PixelMode();
		inline void FillPixel();
		inline void FillTmpPixel();
		inline void UndoPixel();
		inline void PixelEraser();
		inline bool PixelEraserFlag();
		inline void DrawCanvas();
		inline void DrawGlutLine();
		inline void DrawPixel();
		inline void DrawDisplay();
		inline void Status();
};


inline GRAPPA::GRAPPA():ColorBarArray(500){
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
		for(int j=0;j<Xpixel;++j){
			for(int k=0;k<Ypixel;++k){
				Pixel[i][j][k] = 1.0;
				TmpPixel[i][j][k] = 1.0;
			}
		}
	}
	ColorBarWidth = new double[ColorBarArray];
	for(int i=0;i<ColorBarArray;++i)
		ColorBarWidth[i] = 3.0;
	LineID   = 0;
	DrawMode = MFREEHAND;
	TmpFlag  = false;
	PXFLAG   = false;
	ERFLAG   = false;
	STFLAG   = true;
	PixelSize  = 1;
	PixelEraserCounter = 0;
}


inline GRAPPA::~GRAPPA(){
	delete[] ColorBarWidth;
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
		for(int j=0;j<Xpixel;++j){
			for(int k=0;k<Ypixel;++k){
				Pixel[i][j][k] = 1.0;
				TmpPixel[i][j][k] = 1.0;
			}
		}
	}
	LineID = 0;
}


inline void GRAPPA::NewFreeHand(){
	if(DrawMode==MFREEHAND){
		LineID++;
		if(LineNum<LineID) LineID = 0;
		Counter[LineID] = 0;
		if(ERFLAG) ++PixelEraserCounter;
	}
}


inline void GRAPPA::Undo(){
	//UndoPixel();
	TmpCount[LineID] = Counter[LineID];
	Counter[LineID] = 0;
	if(0<LineID) --LineID;
}


inline void GRAPPA::Redo(){
	if(LineID+1<LineNum){
		if(Px[0][LineID+1] && Py[0][LineID+1]){
			++LineID;
			Counter[LineID] = 0;
			for(int i=0;i<=TmpCount[LineID];++i){
				//FillPixel();
				++Counter[LineID];
			}
			Counter[LineID] = TmpCount[LineID];
		}
	}
}


inline void GRAPPA::EraseLine(){
	if(Counter[LineID]) --Counter[LineID];
	else if(LineID) --LineID;
}


inline void GRAPPA::DrawColorBar(){
	if(DrawMode==MCOLORBARLINE||DrawMode==MCOLORBARCANVAS){
		double hmax = 1.0;
		double hbin = hmax/ColorBarArray;
		int i = 0;
		glBegin(GL_QUADS);
		for(double h=0.0;h<hmax;h+=hbin){
			hue2rgb hue(h,hmax);
			glColor3d(hue.R(),hue.G(),hue.B());
			double yoff = Cmargin+5;
			glVertex2d(h     ,(yoff)/100);
			glVertex2d(h+hbin,(yoff)/100);
			glVertex2d(h+hbin,(yoff+ColorBarWidth[i])/100);
			glVertex2d(h     ,(yoff+ColorBarWidth[i])/100);
			++i;
		}
		glEnd();
	}
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
	if(R==G && G==B)
		SetDefaultLineColor(0.5-R,0.5-G,1.0-B);
	else
		SetDefaultLineColor(1.0-R,1.0-G,1.0-B);
	FillTmpPixel();
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
	if(5.0<w) w = 5.0;
	for(int i=LineID+1;i<LineNum;++i){
		LineWidth[i] = w;
	}
}


inline void GRAPPA::SetPixelSize(int size){
	static int max = 10;
	if(1<size && size<max) PixelSize = size;
	else if(max<=size)     PixelSize = max;
	else                   PixelSize = 1;
}


inline int GRAPPA::CurrentDrawMode(){
	return DrawMode;
}


inline void GRAPPA::SetDrawMode(int mode){
	if(DrawMode==MCOLORBARLINE||\
		DrawMode==MCOLORBARCANVAS){
		for(int i=0;i<ColorBarArray;++i)
			ColorBarWidth[i] = 3.0;
		printf("\n");
	}
	if(TmpFlag) TmpFlag = false;
	DrawMode = mode;
}


inline void GRAPPA::SetDrawMode(int mode, int N_side){
	if(mode==MPOLYGON){
		Nside = N_side;
		if(N_side<3) Nside = 3;
		if(CircleSample<N_side) Nside = CircleSample;
		DrawMode = MPOLYGON;
	}
}


inline void GRAPPA::SetCoordinate(int x, int y){
	switch(DrawMode){
		case MFREEHAND: /* Store Coordinate */
			{
				if(!TmpFlag){
					FillTmpPixel();
					TmpFlag = true;
				}
				if(Counter[LineID]<FreeMAX){
					Px[Counter[LineID]][LineID] = x;
					Py[Counter[LineID]][LineID] = y;
					Counter[LineID]++;
				}
				else{
					LineID++;
					if(LineNum<=LineID) LineID = 0;
					if(ERFLAG) ++PixelEraserCounter;
				}
				FillPixel();
			}
			break;
		case MCOLORBARLINE: /* Set Line Color by ColorBar */
			{
				int ch = (int)((double)x/WX*ColorBarArray);
				static double s = 15.0/WX*ColorBarArray;
				while(ch<0) ch += ColorBarArray;
				while(ColorBarArray<=ch) ch -= ColorBarArray;
				for(int i=0;i<ColorBarArray;++i)
					ColorBarWidth[i] = 3.0+exp(-(i-ch)*(i-ch)/(2*s*s));
				hue2rgb C(x,WX);
				SetLineColor(C.R(),C.G(),C.B());
				SetDefaultLineColor(C.R(),C.G(),C.B());
				printf("\r\tR:%f\tG:%f\tB:%f",C.R(),C.G(),C.B());
				fflush(stdout);
			}
			break;
		case MCOLORBARCANVAS: /* Set Canvas Color by ColorBar */
			{
				int ch = (int)((double)x/WX*ColorBarArray);
				static double s = 15.0/WX*ColorBarArray;
				while(ch<0) ch += ColorBarArray;
				while(ColorBarArray<=ch) ch -= ColorBarArray;
				for(int i=0;i<ColorBarArray;++i)
					ColorBarWidth[i] = 3.0+exp(-(i-ch)*(i-ch)/(2*s*s));
				hue2rgb C(x,WX);
				SetCanvasColor(C.R(),C.G(),C.B());
				printf("\r\tR:%f\tG:%f\tB:%f",C.R(),C.G(),C.B());
				fflush(stdout);
			}
			break;
		case MCIRCLE: /* Draw Circle */
			SetLineCircle(x,y);
			break;
		case MSQUARE: /* Draw Square */
			SetLineSquare(x,y);
			break;
		case MPOLYGON: /* Draw N-side Polygon */
			SetLinePolygon(x,y);
			break;
		case MSTRAIGHTLINE: /* Draw Straight Line */
			SetStraightLine(x,y);
			break;
		case MRANDOM: /* Draw Random */
			SetRandom(x,y);
			break;
		case MKALEIDO: /* Draw Kaleido */
			SetKaleido(x,y);
			break;
		case MLINEMOVE: /* Line Move */
			LineMove(x,y);
			break;
		case MLINECOPY: /* Line Copy */
			LineCopy(x,y);
			break;
		case MLINEROTATE: /* Line Rotate */
			LineRotate(x,y);
			break;
		default:
			break;
	}
}


inline void GRAPPA::SetLineCircle(int x, int y){
	static int x0;
	static int y0;
	if(!TmpFlag){
		++LineID;
		FillTmpPixel();
		x0 = x;
		y0 = y;
		TmpFlag = true;
	}
	UndoPixel();
	double xc = (x+x0)/2;
	double yc = (y+y0)/2;
	double r  = sqrt(pow(x-xc,2)+pow(y-yc,2));
	Counter[LineID] = 0;
	for(int i=0;i<=CircleSample;++i){
		Px[Counter[LineID]][LineID] = xc+r*cos((double)i/CircleSample*2*PI);
		Py[Counter[LineID]][LineID] = yc+r*sin((double)i/CircleSample*2*PI);
		++Counter[LineID];
		FillPixel();
	}
}


inline void GRAPPA::SetLineSquare(int x, int y){
	static int x0;
	static int y0;
	if(!TmpFlag){
		++LineID;
		FillTmpPixel();
		x0 = x;
		y0 = y;
		TmpFlag = true;
	}
	UndoPixel();
	Counter[LineID] = 0;
	for(int i=0;i<=4;++i){
		Px[Counter[LineID]][LineID] = (((i+2)%4)/2)*x0+((i%4)/2)*x;
		Py[Counter[LineID]][LineID] = (((i+3)%4)/2)*y0+(((i+1)%4)/2)*y;
		++Counter[LineID];
		FillPixel();
	}
}


inline void GRAPPA::SetLinePolygon(int x, int y){
	static int x0;
	static int y0;
	if(!TmpFlag){
		++LineID;
		FillTmpPixel();
		x0 = x;
		y0 = y;
		TmpFlag = true;
	}
	UndoPixel();
	double xc = (x+x0)/2;
	double yc = (y+y0)/2;
	double r  = sqrt(pow(x-xc,2)+pow(y-yc,2));
	Counter[LineID] = 0;
	for(int i=0;i<=Nside;++i){
		Px[Counter[LineID]][LineID] = xc+r*sin((double)i/Nside*2*PI);
		Py[Counter[LineID]][LineID] = yc-r*cos((double)i/Nside*2*PI);
		++Counter[LineID];
		FillPixel();
	}
}


inline void GRAPPA::SetStraightLine(int x, int y){
	if(!TmpFlag){
		++LineID;
		FillTmpPixel();
		Px[0][LineID] = x;
		Py[0][LineID] = y;
		TmpFlag = true;
	}
	UndoPixel();
	Px[1][LineID] = x;
	Py[1][LineID] = y;
	Counter[LineID] = 2;
	FillPixel();
}


inline void GRAPPA::SetRandom(int x, int y){
	if(!TmpFlag){
		++LineID;
		TmpFlag = true;
	}
	Px[Counter[LineID]][LineID] = x+10*(2*randf()-1)*LineWidth[LineID];
	Py[Counter[LineID]][LineID] = y+10*(2*randf()-1)*LineWidth[LineID];
	++Counter[LineID];
	if(FreeMAX<=Counter[LineID]) ++LineID;
	FillPixel();
}


inline void GRAPPA::SetKaleido(int x, int y){
	static int x0;
	static int y0;
	if(!TmpFlag){
		hue2rgb C(LineID,20);
		SetDefaultLineColor(C.R(),C.G(),C.B());
		++LineID;
		FillTmpPixel();
		x0 = x;
		y0 = y;
		TmpFlag = true;
	}
	double xc = (x+x0)/2;
	double yc = (y+y0)/2;
	double r  = sqrt(pow(x-xc,2)+pow(y-yc,2));
	double theta,a;
	if(r==0) theta = 0.0;
	else{
		a = (x0-xc)/r;
		if(a<-1) a =-1.0;
		if(1<a)  a = 1.0;
		theta = acos(a);
	}
	for(int i=0;i<=CircleSample;++i){
		Px[Counter[LineID]][LineID] = xc+r*cos((double)i/CircleSample*2*PI+theta);
		Py[Counter[LineID]][LineID] = yc+r*sin((double)i/CircleSample*2*PI+theta);
		++Counter[LineID];
		if(FreeMAX-1<Counter[LineID]){
			hue2rgb C(LineID,20);
			SetDefaultLineColor(C.R(),C.G(),C.B());
			++LineID;
		}
		FillPixel();
	}
}


inline void GRAPPA::LineMove(int x, int y){
	if(0<Counter[LineID]){
		static int x0 = x;
		static int y0 = y;
		if(!TmpFlag){
			x0 = x;
			y0 = y;
			TmpFlag = true;
		}
		UndoPixel();
		int max = Counter[LineID];
		Counter[LineID] = 0;
		for(int i=0;i<max;++i){
			Px[i][LineID] += x-x0;
			Py[i][LineID] += y-y0;
			++Counter[LineID];
			FillPixel();
		}
		x0 = x;
		y0 = y;
	}
}


inline void GRAPPA::LineCopy(int x, int y){
	if(0<Counter[LineID]){
		static int x0 = x;
		static int y0 = y;
		if(!TmpFlag){
			FillTmpPixel();
			x0 = x;
			y0 = y;
			++LineID;
			Counter[LineID] = 0;
			for(int i=0;i<Counter[LineID-1];++i){
				Px[i][LineID] = Px[i][LineID-1];
				Py[i][LineID] = Py[i][LineID-1];
				++Counter[LineID];
			}
			TmpFlag = true;
		}
		UndoPixel();
		int max = Counter[LineID];
		Counter[LineID] = 0;
		for(int i=0;i<max;++i){
			Px[i][LineID] += x-x0;
			Py[i][LineID] += y-y0;
			++Counter[LineID];
			FillPixel();
		}
		x0 = x;
		y0 = y;
	}
}


inline void GRAPPA::LineRotate(int x, int y){
	if(0<LineID){
		static int x0 = x;
		static int y0 = y;
		static double xc,yc;
		static double dot,vec0,vec1,theta; 
		if(!TmpFlag){
			xc = (Px[0][LineID]+Px[Counter[LineID]-1][LineID])/2.0;	
			yc = (Py[0][LineID]+Py[Counter[LineID]-1][LineID])/2.0;	
			TmpFlag = true;
		}
		UndoPixel();
		dot   = (x0-xc)*(x-xc)+(y0-yc)*(y-yc);
		vec0  = sqrt(pow(x0-xc,2)+pow(y0-yc,2));
		vec1  = sqrt(pow(x-xc,2)+pow(y-yc,2));
		double a = dot/(vec0*vec1);
		if(a<-1) a = -1.0;
		if(1<a)  a =  1.0;
		theta = acos(a);
		if(vec0==0 || vec1==0) theta = 0.0;
		int max = Counter[LineID];
		Counter[LineID] = 0;
		for(int i=0;i<max;++i){
			double X = Px[i][LineID];
			double Y = Py[i][LineID];
			Px[i][LineID] = xc+(X-xc)*cos(theta)-(Y-yc)*sin(theta);
			Py[i][LineID] = yc+(X-xc)*sin(theta)+(Y-yc)*cos(theta);
			++Counter[LineID];
			FillPixel();
		}
		x0 = x;
		y0 = y;
	}
}


inline void GRAPPA::PixelMode(){
	if(PXFLAG) PXFLAG = false;
	else      PXFLAG = true;
}


#define PixelBlottingOut(x,y)\
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
		else //v==0
			PixelBlottingOut(Px[c][LineID],Py[c][LineID]);
	}
	else //c<=0
		PixelBlottingOut(Px[0][LineID],Py[0][LineID]);
}
#undef PixelBlottingOut


inline void GRAPPA::FillTmpPixel(){
	for(int i=0;i<3;++i){
		for(int j=0;j<Xpixel;++j){
			for(int k=0;k<Ypixel;++k){
				TmpPixel[i][j][k] = Pixel[i][j][k];
			}
		}
	}
}


inline void GRAPPA::UndoPixel(){
	for(int i=0;i<3;++i){
		for(int j=0;j<Xpixel;++j){
			for(int k=0;k<Ypixel;++k){
				if(Pixel[i][j][k]!=TmpPixel[i][j][k])
					Pixel[i][j][k] = TmpPixel[i][j][k];
			}
		}
	}
}


inline void GRAPPA::PixelEraser(){
	if(PXFLAG){
		static int TmpPixelSize = 2;
		static double TmpColor[3];
		if(!ERFLAG){ // Eraser ON
			ERFLAG = true;
			TmpPixelSize = PixelSize;
			PixelSize = 20;
			for(int i=0;i<3;++i)
				TmpColor[i] = LineColor[i][LineID];
			SetDefaultLineColor(CanvasColor[0],CanvasColor[1],CanvasColor[2]);
		}
		else{ // Eraser OFF
			ERFLAG = false;
			if(PixelEraserCounter){
				for(int i=0;i<PixelEraserCounter;++i){
					TmpCount[LineID] = Counter[LineID];
					Counter[LineID] = 0;
					if(0<LineID) --LineID;
				}
				PixelEraserCounter = 0;
			}
			PixelSize = TmpPixelSize;
			SetDefaultLineColor(TmpColor[0],TmpColor[1],TmpColor[2]);
		}
	}
}


inline bool GRAPPA::PixelEraserFlag(){
	return ERFLAG;
}


inline void GRAPPA::DrawCanvas(){
	if(!PXFLAG){
		glColor3d(CanvasColor[0],CanvasColor[1],CanvasColor[2]);
		glBegin(GL_QUADS);
		glVertex2d(Cmargin/100,Cmargin/100);
		glVertex2d((100-Cmargin)/100,Cmargin/100);
		glVertex2d((100-Cmargin)/100,(100-Cmargin)/100);
		glVertex2d(Cmargin/100,(100-Cmargin)/100);
		glEnd();
	}
}


inline void GRAPPA::DrawGlutLine(){
	if(!PXFLAG){
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


inline void GRAPPA::DrawPixel(){
	if(PXFLAG){
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


inline void GRAPPA::DrawDisplay(){
	if(CanvasColor[0]==CanvasColor[1]&&CanvasColor[1]==CanvasColor[2])
		glColor3d(0.5-CanvasColor[0],0.5-CanvasColor[1],1.0-CanvasColor[2]);
	else
		glColor3d(1.0-CanvasColor[0],1.0-CanvasColor[1],1.0-CanvasColor[2]);
	char s[128];
	if(STFLAG){
		int x = (Counter[LineID]>1)? Px[Counter[LineID]-1][LineID]:0;
		int y = (Counter[LineID]>1)? Py[Counter[LineID]-1][LineID]:0;
		sprintf(s,"[%d,%d]",x,y);
		glDrawString(s,(Cmargin+1)/100,(100-Cmargin-3)/100);
		sprintf(s,"Line No. %d Length %d",LineID,Counter[LineID]);
		glDrawString(s,(Cmargin+1)/100,(100-Cmargin-6)/100);

		if(PXFLAG){
			if(ERFLAG)
				glDrawString("Mode : Pixel(Eraser)",(Cmargin+1)/100,(100-Cmargin-9)/100);
			else
				glDrawString("Mode : Pixel",(Cmargin+1)/100,(100-Cmargin-9)/100);
		}
		else
			glDrawString("Mode : GLUT Line",(Cmargin+1)/100,(100-Cmargin-9)/100);
	}
}


inline void GRAPPA::Status(){
	if(STFLAG) STFLAG = false;
	else STFLAG = true;
}


/*****************************/

#endif //GRAPPA_h_
