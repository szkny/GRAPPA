/*
*	GRAPPA Commands Configurations 
*/

#include<GL/glut.h>
#include<GRAPPA.h>

extern bool MFLAG; //defined in Mouse.cpp
extern bool M_Nodrag; //defined in Mouce.cpp
extern GRAPPA Drawing;

void MouseDrawMode(void);
void KeyboardMode(void);
void KeyboardShortcut(unsigned char key, int x, int y);
void MNDrag(void);


void Commands(){
	double Arg1,Arg2,Arg3;

	if(Drawing.RunCommand("q","quit","exit"))
		exit(0);

	else if(Drawing.RunCommand("undo"))
		Drawing.Undo();

	else if(Drawing.RunCommand("redo"))
		Drawing.Redo();
	
	else if(Drawing.RunCommand("nodrag"))
		MNDrag();
	
	else if(Drawing.RunCommand("status"))
		Drawing.Status();

	else if(Drawing.RunCommand("reset"))
		Drawing.Reset();

	else if(Drawing.RunCommand("setid",&Arg1))
		Drawing.SetLineID(Arg1);

	else if(Drawing.RunCommand("backid"))
		Drawing.BackLineID();
		
	else if(Drawing.RunCommand("co"))
		Drawing.SetDrawMode(DCOLORBARLINE);

	else if(Drawing.RunCommand("co",&Arg1,&Arg2,&Arg3))
		Drawing.SetLineColor(Arg1,Arg2,Arg3);

	else if(Drawing.RunCommand("cco"))
		Drawing.SetDrawMode(DCOLORBARCANVAS);

	else if(Drawing.RunCommand("cco",&Arg1,&Arg2,&Arg3))
		Drawing.SetCanvasColor(Arg1,Arg2,Arg3);

	else if(Drawing.RunCommand("dco",&Arg1,&Arg2,&Arg3))
		Drawing.SetDefaultLineColor(Arg1,Arg2,Arg3);

	else if(Drawing.RunCommand("cor"))
		Drawing.SetLineColor(1.0,0.0,0.0);

	else if(Drawing.RunCommand("cog"))
		Drawing.SetLineColor(0.0,1.0,0.0);

	else if(Drawing.RunCommand("cob"))
		Drawing.SetLineColor(0.0,0.0,1.0);

	else if(Drawing.RunCommand("coy"))
		Drawing.SetLineColor(1.0,1.0,0.0);

	else if(Drawing.RunCommand("lw",&Arg1))
		Drawing.SetLineWidth(Arg1);

	else if(Drawing.RunCommand("dlw",&Arg1))
		Drawing.SetDefaultLineWidth(Arg1);

	else if(Drawing.RunCommand("p","pixel"))
		Drawing.PixelMode();

	else if(Drawing.RunCommand("ps",&Arg1))
		Drawing.SetPixelSize(Arg1);

	else if(Drawing.RunCommand("eraser"))
		Drawing.PixelEraser();

	else if(Drawing.RunCommand("circle"))
		Drawing.SetDrawMode(DCIRCLE);

	else if(Drawing.RunCommand("square"))
		Drawing.SetDrawMode(DSQUARE);

}


void InputKey(unsigned char key, int x, int y){
	if(key == 127){ //delete key
		int size = Drawing.CommandStore(key);
		if(size == 0) KeyboardMode();
	}
	else if(key == 13){ //return key
		Commands();
		Drawing.CommandStore(key);
		KeyboardMode();
	}
	else if(key == 9){ //tab key
		;
	}
	else{
		Drawing.CommandStore(key);
	}
}


/* arrow key */
void keyboard_sp(int key, int x, int y){
	if(key==GLUT_KEY_UP||key==GLUT_KEY_DOWN)
		Drawing.CommandHistory(key);
	if(key==GLUT_KEY_RIGHT||key==GLUT_KEY_LEFT)
		Drawing.CommandCursor(key);
}

