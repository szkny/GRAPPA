/* main.cpp
 *
 *  main source for GRAPPA PAINT
 *      (c) M.Haroon, S.Suzuki 2017.4.26 (origin)
 *          patch ———— 2017.6.19 (vol0.2.2)
 */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>

#ifdef __APPLE__
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
void Timer(int value);
void Resize(int w, int h);
void MouseClick(int button, int state, int x, int y);
void keyboard_sp(int key, int x, int y);

/* Declaration of new GRAPPA class */
GRAPPA Drawing;
Command Cmd;

/* main function */
int main(int argc, char *argv[]){
    srand((unsigned) time(NULL));
    printf("\n\t\033[7m Welcom to GRAPPA \033[0m\n"
            " please type ':' key to input commands.\n\n");
    fflush(stdout);
    glutInit(&argc, argv);
    WindowCanvas();
    PopUpMenu();
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
    glutTimerFunc(10,Timer,0);
    glutReshapeFunc(Resize);
    glClearColor(0.2,0.2,0.2,1.0);
    Drawing.Init();
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
    Drawing.DrawLine();
    Drawing.DrawColorBar();
    Drawing.DrawDisplay();
    Cmd.DrawCommand();
    glutIdleFunc(glutPostRedisplay);
    glFlush();
}


void Timer(int value){
    Controler();
    glutPostRedisplay();
    glutTimerFunc(60,Timer,0);
}


void Resize(int w, int h){
    glViewport(0, 0, w ,h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    Drawing.Resize(w,h);
    Cmd.Resize(w,h);
}


