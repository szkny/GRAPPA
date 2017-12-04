/*
 *  PopupMenu Configurations
 */

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<MyGLUT.h>

extern GRAPPA Drawing;

void Menu(int val);

void PopUpMenu(void){
    /* Sub Menu */
    int MenuID = glutCreateMenu(Menu);
    glutAddMenuEntry("line",100);
    glutAddMenuEntry("circle",101);
    glutAddMenuEntry("square",102);
    glutAddMenuEntry("random",103);
    glutAddMenuEntry("kaleido",104);
    /* Main Menu */
    glutCreateMenu(Menu);
    glutAddMenuEntry("Select Line Color",1);
    glutAddMenuEntry("Reset",2);
    glutAddMenuEntry("Undo",3);
    glutAddMenuEntry("Copy",4);
    glutAddMenuEntry("Move",5);
    glutAddMenuEntry("Pixel Mode",6);
    glutAddSubMenu("Drawing Mode",MenuID);
    glutAddMenuEntry("Quit",0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
    switch(val){
        case 0: /* Quit */
            exit(0);
        case 1: /* Select Line Color */
            Drawing.SetDrawMode(MCOLORBARLINE);
            break;
        case 2: /* Reset Lines */
            Drawing.Reset();
            break;
        case 3: /* Undo */
            Drawing.Undo();
            break;
        case 4: /* Copy */
            Drawing.SetDrawMode(MLINECOPY);
            break;
        case 5: /* Move */
            Drawing.SetDrawMode(MLINEMOVE);
            break;
        case 6: /* Pixel Mode */
            Drawing.PixelMode();
            break;
        case 100: /* Draw Line */
            Drawing.SetDrawMode(MSTRAIGHTLINE);
            break;
        case 101: /* Draw Circle */
            Drawing.SetDrawMode(MCIRCLE);
            break;
        case 102: /* Draw Square */
            Drawing.SetDrawMode(MSQUARE);
            break;
        case 103: /* Draw Random */
            Drawing.SetDrawMode(MRANDOM);
            break;
        case 104: /* Draw Kaleido */
            Drawing.SetDrawMode(MKALEIDO);
            break;
        default:
            break;
    }
}

