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

extern GRAPPA Gra;
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
    glutAddSubMenu("Gra Mode",MenuID);
    glutAddMenuEntry("Quit",POPUP_QUIT);
    /* Assign Menu Button */
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void Menu(int val){
    switch(val){
        case POPUP_QUIT: /* Quit */
            exit(0);
        case POPUP_LINECOLOR: /* Select Line Color */
            Gra.SetDrawMode(MCOLORBARLINE);
            break;
        case POPUP_CANVASCOLOR: /* Select Line Color */
            Gra.SetDrawMode(MCOLORBARCANVAS);
            break;
        case POPUP_RESET: /* Reset Lines */
            Gra.Reset();
            break;
        case POPUP_UNDO: /* Undo */
            Gra.Undo();
            break;
        case POPUP_REDO: /* Redo */
            Gra.Redo();
            break;
        case POPUP_COPY: /* Copy */
            Gra.SetDrawMode(MLINECOPY);
            break;
        case POPUP_MOVE: /* Move */
            Gra.SetDrawMode(MLINEMOVE);
            break;
        case POPUP_PIXEL: /* Pixel Mode */
            Gra.PixelMode();
            break;
        case POPUP_STRAIGHTLINE: /* Draw Line */
            Gra.SetDrawMode(MSTRAIGHTLINE);
            break;
        case POPUP_CIRCLE: /* Draw Circle */
            Gra.SetDrawMode(MCIRCLE);
            break;
        case POPUP_SQUARE: /* Draw Square */
            Gra.SetDrawMode(MSQUARE);
            break;
        case POPUP_RANDOM: /* Draw Random */
            Gra.SetDrawMode(MRANDOM);
            break;
        // case POPUP_KALEIDO: #<{(| Draw Kaleido |)}>#
        //     Gra.SetDrawMode(MKALEIDO);
        //     break;
        default:
            break;
    }
}

