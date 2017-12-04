/*
 *  Mouse Configurations
 */

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>

bool MFLAG;
extern GRAPPA Drawing;


/* mouse click */
void MouseClick(int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
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
    glutPassiveMotionFunc(NULL);
    glutMotionFunc(MouseMotion);
}


