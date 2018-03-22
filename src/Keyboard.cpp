/*
 *  Keyboard Shortcuts Configurations
 */

#include<GRAPPA.h>
#include<Command.h>

extern bool MFLAG;    //defined in Mouse.cpp
extern GRAPPA  Gra;
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
            Gra.Undo();
            break;
        case 'c': /* Color */
            Gra.SetDrawMode(MCOLORBARLINE);
            break;
        case 'r': /* Redo */
            Gra.Redo();
            break;
        case 'e': /* Erase */
            Gra.EraseLine();
            break;
        case 'p': /* Pixel Mode */
            Gra.PixelMode();
            break;
        case 's': /* Show Status */
            Gra.ShowStatus();
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

