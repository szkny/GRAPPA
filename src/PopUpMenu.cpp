/*
*	PopupMenu Configurations
*/
#include<GL/glut.h>
#include<MyGLUT.h>


void Menu(int val);

void PopUpMenu(void){
	glutCreateMenu(Menu);
	glutAddMenuEntry("Quit",0);
    //glutAddMenuEntry("select color",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
	switch(val){
		case 0:  /* Quit */
			exit(0);
		default:
			break;
	}
}
