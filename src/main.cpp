/* main.cpp
*
*	main source for GRAPPA PAINT  
*		(c) M.Haroon, S.Suzuki 2017.4.26 (origin)
*					patch ———— 2017.6.19 (vol0.2.2)
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<Command.h>

/* Function Prototype Declaration */
void WindowCanvas(void);
void Controler(void);
void MouseDrawMode(void);
void KeyboardMode(void);
void PopUpMenu(void);
void Display(void);
void Resize(int w, int h);
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void KeyboardShortcut(unsigned char key, int x, int y);
void CommandLine(unsigned char key, int x, int y);
void keyboard_sp(int key, int x, int y);

/* Declaration of new GRAPPA class */
GRAPPA Drawing;
Command Cmd;

/* main function */
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	WindowCanvas();
	PopUpMenu();
	Controler();
	glutMainLoop();
	return 0;
}

/******** Functions *********/

void WindowCanvas(void){
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,400);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow("GRAPPA PAINT");
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glClearColor(0.2,0.2,0.2,1.0);
}


void Controler(void){
	glutMouseFunc(MouseClick);
	MouseDrawMode();
	KeyboardMode();
	glutSpecialFunc(keyboard_sp);
}


void Display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	Drawing.DrawPixel();
	Drawing.DrawCanvas();
	Drawing.DrawGlutLine();
	Drawing.DrawColorBar();
	Drawing.DrawDisplay();
	Cmd.DrawCommand();
	glutIdleFunc(glutPostRedisplay);
	glFlush();
}


void Resize(int w, int h){
	glViewport(0, 0, w ,h);
	glLoadIdentity();
	gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	Drawing.Init(w,h);
}


