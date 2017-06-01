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


void Commands(){

	double Arg1,Arg2,Arg3;

	if(Drawing.RunCommand("q","quit","exit"))
		exit(0);

	if(Drawing.RunCommand("u","undo"))
		Drawing.Undo();

	if(Drawing.RunCommand("n","nodrag")){
		if(M_Nodrag){
			M_Nodrag = false;
			MFLAG = false;
		}
		else {
			M_Nodrag = true;
			MFLAG = true;
			Drawing.NewFreeHand();
		}
		MouseDrawMode();
	}

	if(Drawing.RunCommand("cor"))
		Drawing.SetColor(1.0,0.0,0.0);

	if(Drawing.RunCommand("cog"))
		Drawing.SetColor(0.0,1.0,0.0);

	if(Drawing.RunCommand("cob"))
		Drawing.SetColor(0.0,0.0,1.0);

	if(Drawing.RunCommand("coy"))
		Drawing.SetColor(1.0,1.0,0.0);

	if(Drawing.RunCommand("co",&Arg1,&Arg2,&Arg3))
		Drawing.SetColor(Arg1,Arg2,Arg3);

	if(Drawing.RunCommand("dco",&Arg1,&Arg2,&Arg3))
		Drawing.SetDefaultColor(Arg1,Arg2,Arg3);

	if(Drawing.RunCommand("lw",&Arg1))
		Drawing.SetLineWidth(Arg1);

	if(Drawing.RunCommand("dlw",&Arg1))
		Drawing.SetDefaultLineWidth(Arg1);
		
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
	else{
		Drawing.CommandStore(key);
	}
}


/* arrow key */
void keyboard_sp(int key, int x, int y){
	Drawing.CommandHistory(key);
}

