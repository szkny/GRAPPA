/*
 *  Mouse Configurations
 */

#ifdef __APPLE__
// #include<GLUT/glut.h>
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>

bool MFLAG;
bool M_Nodrag;
extern GRAPPA Drawing;


/* mouse click */
void MouseClick(int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if(M_Nodrag){
                if(state==GLUT_UP){
                    Drawing.NewFreeHand();
                    Drawing.SetCoordinate(x,y);
                }
                if(state==GLUT_DOWN){
                    MFLAG = false;
                    Drawing.SetDrawMode();
                    if(Drawing.PixelEraserFlag())
                        Drawing.PixelEraser();
                }
            }
            else{
                if(state==GLUT_DOWN){
                    Drawing.NewFreeHand();
                    Drawing.SetCoordinate(x,y);
                }
                if(state==GLUT_UP){
                    MFLAG = false;
                    Drawing.SetDrawMode();
                    if(Drawing.PixelEraserFlag())
                        Drawing.PixelEraser();
                }
            }
            break;
        default:
            break;
    }
}


/* mouse motion */
void MouseMotion(int x, int y){
    if(MFLAG){
        Drawing.SetCoordinate(x,y);
    }
    MFLAG  = true;
}


void MouseDrawMode(void){
    if(M_Nodrag) {
        glutMotionFunc(NULL);
        glutPassiveMotionFunc(MouseMotion);//allows to draw without Dragging mouse
    }
    else {
        glutPassiveMotionFunc(NULL);
        glutMotionFunc(MouseMotion);
    }
}


void MNDrag(void){
    if(M_Nodrag){
        M_Nodrag = false;
        MFLAG = false;
    }
    else {
        M_Nodrag = true;
        MFLAG = true;
        Drawing.NewFreeHand();
    }
    MouseDrawMode();
}
