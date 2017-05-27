#include<GL/glut.h>
#include<MyGLUT.h>

void menu(int val);

void PopUpMenu(void){
	glutCreateMenu(menu);
	glutAddMenuEntry("Quit",0);
    //glutAddMenuEntry("select color",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int val){
	switch(val){
		case 0:  /* Quit */
			exit(0);
		default:
			break;
	}
}

