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

#include<ctime>
#include<thread>
#include<exception>

#ifdef __APPLE__
#include<GLUT/glut.h>
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
    for(auto _s : Fio.GetFormatID())
        std::cout << _s << std::endl;
    std::cout << " Welcom to GRAPPA. type ':' to input commands.\n"
              << std::endl;
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
    // try{
    //     std::thread thread1(glutDisplayFunc,Display);
    //     std::thread thread2(Controler);
    //     thread1.join();
    //     thread2.join();
    // }catch(std::exception &ex){
    //     std::cerr << ex.what() << std::endl;
    // }
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
    std::cout << "\n Bye :)\n"
              << std::endl;
    exit(0);
}


