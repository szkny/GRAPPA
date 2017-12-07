/*
 *  Keyboard Shortcuts Configurations
 */

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<Command.h>

extern bool MFLAG;    //defined in Mouse.cpp
extern GRAPPA Drawing;
extern Command Cmd;

void MouseDrawMode(void);
void KeyboardMode(void);
void InputKey(unsigned char key, int x, int y);

void KeyboardShortcut(unsigned char key, int x, int y){
    switch(key){
        case 'q': /* Quit */
            exit(0);
            break;
        case 'u': /* Undo */
            Drawing.Undo();
            break;
        case 'c': /* Color */
            Drawing.SetDrawMode(MCOLORBARLINE);
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

