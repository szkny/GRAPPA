/*
 *  Keyboard Shortcuts Configurations
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

extern bool MFLAG;    //defined in Mouse.cpp
extern bool M_Nodrag; //defined in Mouce.cpp
extern GRAPPA Drawing;
extern Command Cmd;

void MouseDrawMode(void);
void KeyboardMode(void);
void InputKey(unsigned char key, int x, int y);
void MNDrag(void);

void KeyboardShortcut(unsigned char key, int x, int y){
    switch(key){
        case 'q': /* Quit */
            exit(0);
            break;
        case 'u': /* Undo */
            Drawing.Undo();
            break;
        case 'r': /* Redo */
            Drawing.Redo();
            break;
        case 'e': /* Erase */
            Drawing.EraseLine();
            break;
        case 'p': /* Pixel Mode */
            Drawing.PixelMode();
            break;
        case 's': /* Show Status */
            Drawing.Status();
            break;
        case 'n': /* Drawing with No Mouse Drag */
            MNDrag();
            break;
        case ':': /* Prompt Mode */
            Cmd.CommandMode();
            KeyboardMode();
            break;
        default:
            break;
    }
}


void KeyboardMode(void){
    if(Cmd.CommandFlag()) glutKeyboardFunc(InputKey);
    else glutKeyboardFunc(KeyboardShortcut);
}


// void keyboard_sp(int key, int x, int y){
//     switch (key) {
//         case GLUT_KEY_RIGHT:
//             break;
//         case GLUT_KEY_LEFT:
//             break;
//         case GLUT_KEY_UP:
//             break;
//         case GLUT_KEY_DOWN:
//             break;
//         default:
//             break;
//     }
// }

