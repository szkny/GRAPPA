/*
 *  PopupMenu Configurations
 */

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>
#include<MyGLUT.h>

extern GRAPPA Drawing;
void Menu(int val);

enum POPUPMODE {
    POPUP_QUIT=0,
    POPUP_LINECOLOR,
    POPUP_CANVASCOLOR,
    POPUP_RESET,
    POPUP_UNDO,
    POPUP_REDO,
    POPUP_COPY,
    POPUP_MOVE,
    POPUP_PIXEL,
    POPUP_STRAIGHTLINE,
    POPUP_CIRCLE,
    POPUP_SQUARE,
    POPUP_RANDOM,
    POPUP_KALEIDO
};

void PopUpMenu(void){
    /* Sub Menu */
    int MenuID = glutCreateMenu(Menu);
    glutAddMenuEntry("line",POPUP_STRAIGHTLINE);
    glutAddMenuEntry("circle",POPUP_CIRCLE);
    glutAddMenuEntry("square",POPUP_SQUARE);
    glutAddMenuEntry("random",POPUP_RANDOM);
    // glutAddMenuEntry("kaleido",POPUP_KALEIDO);
    /* Main Menu */
    glutCreateMenu(Menu);
    glutAddMenuEntry("Select Line Color",POPUP_LINECOLOR);
    glutAddMenuEntry("Select Canvas Color",POPUP_CANVASCOLOR);
    glutAddMenuEntry("Reset All",POPUP_RESET);
    glutAddMenuEntry("Undo",POPUP_UNDO);
    glutAddMenuEntry("Redo",POPUP_REDO);
    glutAddMenuEntry("Copy",POPUP_COPY);
    glutAddMenuEntry("Move",POPUP_MOVE);
    glutAddMenuEntry("Pixel Mode",POPUP_PIXEL);
    glutAddSubMenu("Drawing Mode",MenuID);
    glutAddMenuEntry("Quit",POPUP_QUIT);
    /* Assign Menu Button */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
    switch(val){
        case POPUP_QUIT: /* Quit */
            exit(0);
        case POPUP_LINECOLOR: /* Select Line Color */
            Drawing.SetDrawMode(MCOLORBARLINE);
            break;
        case POPUP_CANVASCOLOR: /* Select Line Color */
            Drawing.SetDrawMode(MCOLORBARCANVAS);
            break;
        case POPUP_RESET: /* Reset Lines */
            Drawing.Reset();
            break;
        case POPUP_UNDO: /* Undo */
            Drawing.Undo();
            break;
        case POPUP_REDO: /* Redo */
            Drawing.Redo();
            break;
        case POPUP_COPY: /* Copy */
            Drawing.SetDrawMode(MLINECOPY);
            break;
        case POPUP_MOVE: /* Move */
            Drawing.SetDrawMode(MLINEMOVE);
            break;
        case POPUP_PIXEL: /* Pixel Mode */
            Drawing.PixelMode();
            break;
        case POPUP_STRAIGHTLINE: /* Draw Line */
            Drawing.SetDrawMode(MSTRAIGHTLINE);
            break;
        case POPUP_CIRCLE: /* Draw Circle */
            Drawing.SetDrawMode(MCIRCLE);
            break;
        case POPUP_SQUARE: /* Draw Square */
            Drawing.SetDrawMode(MSQUARE);
            break;
        case POPUP_RANDOM: /* Draw Random */
            Drawing.SetDrawMode(MRANDOM);
            break;
        // case POPUP_KALEIDO: #<{(| Draw Kaleido |)}>#
        //     Drawing.SetDrawMode(MKALEIDO);
        //     break;
        default:
            break;
    }
}

