/*
*	GRAPPA Commands Configurations 
*/

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<Command.h>

extern bool MFLAG; //defined in Mouse.cpp
extern bool M_Nodrag; //defined in Mouce.cpp
extern GRAPPA Drawing;
extern Command Cmd;

void MouseDrawMode(void);
void KeyboardMode(void);
void KeyboardShortcut(unsigned char key, int x, int y);
void MNDrag(void);


void Commands(){
	double Arg1,Arg2,Arg3;

	if(Cmd.RunCommand("q","quit","exit"))
		exit(0);

	else if(Cmd.RunCommand("h","help"))
		Cmd.Help();

	else if(Cmd.RunCommand("undo"))
		Drawing.Undo();

	else if(Cmd.RunCommand("redo"))
		Drawing.Redo();
	
	else if(Cmd.RunCommand("nodrag"))
		MNDrag();
	
	else if(Cmd.RunCommand("status"))
		Drawing.Status();

	else if(Cmd.RunCommand("reset"))
		Drawing.Reset();

	else if(Cmd.RunCommand("mv"))
		Drawing.SetDrawMode(MLINEMOVE);
		
	else if(Cmd.RunCommand("cp"))
		Drawing.SetDrawMode(MLINECOPY);
		
	else if(Cmd.RunCommand("rotate"))
		Drawing.SetDrawMode(MLINEROTATE);
		
	else if(Cmd.RunCommand("co"))
		Drawing.SetDrawMode(MCOLORBARLINE);

	else if(Cmd.RunCommand("co",&Arg1,&Arg2,&Arg3))
		Drawing.SetLineColor(Arg1,Arg2,Arg3);

	else if(Cmd.RunCommand("cco"))
		Drawing.SetDrawMode(MCOLORBARCANVAS);

	else if(Cmd.RunCommand("cco",&Arg1,&Arg2,&Arg3))
		Drawing.SetCanvasColor(Arg1,Arg2,Arg3);

	else if(Cmd.RunCommand("dco",&Arg1,&Arg2,&Arg3))
		Drawing.SetDefaultLineColor(Arg1,Arg2,Arg3);

	else if(Cmd.RunCommand("cor"))
		Drawing.SetLineColor(1.0,0.0,0.0);

	else if(Cmd.RunCommand("cog"))
		Drawing.SetLineColor(0.0,1.0,0.0);

	else if(Cmd.RunCommand("cob"))
		Drawing.SetLineColor(0.0,0.0,1.0);

	else if(Cmd.RunCommand("coy"))
		Drawing.SetLineColor(1.0,1.0,0.0);

	else if(Cmd.RunCommand("lw","width",&Arg1))
		Drawing.SetLineWidth(Arg1);

	else if(Cmd.RunCommand("dlw","defaultwidth",&Arg1))
		Drawing.SetDefaultLineWidth(Arg1);

	else if(Cmd.RunCommand("p","pixel"))
		Drawing.PixelMode();

	else if(Cmd.RunCommand("ps","pixelsize",&Arg1))
		Drawing.SetPixelSize(Arg1);

	else if(Cmd.RunCommand("eraser"))
		Drawing.PixelEraser();

	else if(Cmd.RunCommand("circle"))
		Drawing.SetDrawMode(MCIRCLE);

	else if(Cmd.RunCommand("square"))
		Drawing.SetDrawMode(MSQUARE);

	else if(Cmd.RunCommand("polygon",&Arg1))
		Drawing.SetDrawMode(MPOLYGON,Arg1);

	else if(Cmd.RunCommand("line"))
		Drawing.SetDrawMode(MSTRAIGHTLINE);

	else if(Cmd.RunCommand("rand"))
		Drawing.SetDrawMode(MRANDOM);

	else if(Cmd.RunCommand("kaleido"))
		Drawing.SetDrawMode(MKALEIDO);

}


void InputKey(unsigned char key, int x, int y){
	if(key == 127){ //delete key
		int size = Cmd.CommandStore(key);
		if(size == 0) KeyboardMode();
	}
	else if(key == 13){ //return key
		Commands();
		Cmd.CommandStore(key);
		KeyboardMode();
	}
	else if(key == 9){ //tab key
		;
	}
	else{
		Cmd.CommandStore(key);
	}
}


/* arrow key */
void keyboard_sp(int key, int x, int y){
	if(key==GLUT_KEY_UP||key==GLUT_KEY_DOWN)
		Cmd.CommandHistory(key);
	if(key==GLUT_KEY_RIGHT||key==GLUT_KEY_LEFT)
		Cmd.CommandCursor(key);
}

