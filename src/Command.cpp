/*
*	GRAPPA Commands Configurations 
*/

#include<GL/glut.h>
#include<GRAPPA.h>

extern GRAPPA Drawing;

void KeyboardMode(void);
void KeyboardShortcut(unsigned char key, int x, int y);


void Commands(){
	if(Drawing.RunCommand("q","quit","exit"))
		exit(0);
	if(Drawing.RunCommand("u","undo"))
		Drawing.Undo();
}


void InputCommand(unsigned char key, int x, int y){
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

