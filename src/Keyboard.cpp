/*
*	Keyboard Shortcuts Configurations 
*/

#include<GL/glut.h>
#include<GRAPPA.h>

extern bool MFLAG; //defined in Mouse.cpp
extern bool M_Nodrag; //defined in Mouce.cpp
extern GRAPPA Drawing;

void MouseDrawMode(void);
void KeyboardMode(void);
void InputKey(unsigned char key, int x, int y);

void KeyboardShortcut(unsigned char key, int x, int y){
	switch(key){
		case 'u': /* Undo */
			Drawing.Undo();
			break;
		case 's':
			Drawing.Status();
			break;
		case 'n':
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
			break;
		case ':':
			Drawing.CommandMode();
			KeyboardMode();
			break;
		default:
			break;
	}
}


void KeyboardMode(void){
	if(Drawing.CommandFlag()) glutKeyboardFunc(InputKey);
	else glutKeyboardFunc(KeyboardShortcut);
}


//void keyboard_sp(int key, int x, int y){
//	switch (key) {
//		case GLUT_KEY_RIGHT:
//			break;
//		case GLUT_KEY_LEFT:
//			break;
//		case GLUT_KEY_UP:
//			break;
//		case GLUT_KEY_DOWN:
//			break;
//		default:
//			break;
//	}
//}

