/*     ____ ____      _    ____  ____   _
 *    / ___|  _ \    / \  |  _ \|  _ \ / \
 *   | |  _| |_) |  / _ \ | |_) | |_) / _ \
 *   | |_| |  _ <  / ___ \|  __/|  __/ ___ \
 *    \____|_| \_\/_/   \_\_|   |_| /_/   \_\
 *
 * main.cpp
 *  main source code for GRAPPA PAINT
 *      (c) M.Haroon, S.Suzuki 2017.4.26 (origin)
 *          patch ------------ 2018.3.22 (vol1.0.0)
 */

#include<time.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<Command.h>
#include<FileIO.h>
#include<Declaration.h>

/* Declaration of GRAPPA classes */
GRAPPA  Gra;
Command Cmd;
FileIO  Fio;


/* main function */
int main(int argc, char *argv[]){
    srand((unsigned) time(NULL));
    printf("\n\t\033[7m Welcom to GRAPPA \033[0m\n"
            " please type ':' key to input commands.\n\n");
    fflush(stdout);
    glutInit(&argc, argv);
    WindowCanvas();
    PopUpMenu();
    for(int i=1;i<argc;++i) Fio.Load(argv[i]);
    glutMainLoop();
    return 0;
}





/*************** Functions *****************/

void WindowCanvas(void){
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,400);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("GRAPPA PAINT");
    glutDisplayFunc(Display);
    Controler();
    glutTimerFunc(10,Timer,0);
    glutReshapeFunc(Resize);
    glClearColor(0.2,0.2,0.2,1.0);
    Gra.Init();
}


void Controler(void){
    glutMouseFunc(MouseClick);
    MouseDrawMode();
    KeyboardMode();
    glutSpecialFunc(keyboard_sp);
}


void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    Gra.DrawPixel();
    Gra.DrawCanvas();
    Gra.DrawLine();
    Gra.DrawColorBar();
    Gra.DrawDisplay();
    Cmd.DrawCommand();
    Fio.DrawFileName();
    glutSwapBuffers();
}


void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(60,Timer,0);
}


void Resize(int w, int h){
    glViewport(0, 0, w ,h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    Gra.Resize(w,h);
    Cmd.Resize(w,h);
}


void Exit(){
    printf("\n\t\033[7m  Bye :)  \033[0m\n");
    fflush(stdout);
    exit(0);
}


