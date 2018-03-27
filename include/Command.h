#ifndef COMMAND_h_
#define COMMAND_h_

/*****************************/

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<Utility.h>
#include<Colors.h>

#define CmdNum 1000 /* Number of Stored Command */

class Command{
    private:
        int windowW,windowH; /* Window Size */
        bool CMFLAG; /* Command Line Flag */
        char CommandString[CmdNum][100]; /* Input Command String */
        int  CmdID;      /* Command LineID */
        int  CmdCursor;  /* Command Cursor */
        int  HstCounter; /* Go Back Counter for CommandHistory */
    public:
        Command();
        void Resize(int WX, int WY);
        void Help();
        void Notification();
        void DrawCommand();
        void CommandMode();
        bool CommandFlag();
        int  CommandStore(unsigned char key);
        int  CommandHistory(int key);
        void CommandCursor(int key);
        bool RunCommand(const char *s0);
        bool RunCommand(const char *s0, const char *s1);
        bool RunCommand(const char *s0, const char *s1, const char *s2);
        bool RunCommand(const char *s0, double *a1);
        bool RunCommand(const char *s0, double *a1, double *a2);
        bool RunCommand(const char *s0, double *a1, double *a2, double *a3);
        bool RunCommand(const char *s0, double *a1, double *a2, double *a3, double *a4);
        bool RunCommand(const char *s0, const char *s1, double *a1);
        bool RunCommandString(const char *s0, char *arg);
        bool RunCommandString(const char *s0, const char *s1, char *arg);
};


inline Command::Command(){
    CMFLAG = false;
    memset(CommandString,'\0',sizeof(CommandString));
    CmdID = 0;
    CmdCursor = 0;
    HstCounter = 0;
}


inline void Command::Resize(int WX, int WY){
    windowW = WX;
    windowH = WY;
}

inline void Command::Help(){
    printf("\n\033[30m");
    printf( "\033[47m+-------------[ USAGE ]--------------+\033[49m\n"
            "\033[47m| let's try the following commands.  |\033[49m\n"
            "\033[47m|   circle   - draw circle.          |\033[49m\n"
            "\033[47m|   square   - draw square.          |\033[49m\n"
            "\033[47m|   polygon  - draw polygon.         |\033[49m\n"
            "\033[47m|    line    - draw line.            |\033[49m\n"
            "\033[47m|    rand    - draw random line.     |\033[49m\n"
            // "\033[47m|   kaleido  - draw kaleido.         |\033[49m\n"
            "\033[47m|    undo    - undo draw line.       |\033[49m\n"
            "\033[47m|    redo    - redo draw line.       |\033[49m\n"
            "\033[47m|     mv     - move line.            |\033[49m\n"
            "\033[47m|     cp     - copy line.            |\033[49m\n"
            "\033[47m|     co     - change line color.    |\033[49m\n"
            "\033[47m|     lw     - change line width.    |\033[49m\n"
            "\033[47m|   status   - show status.          |\033[49m\n"
            "\033[47m|    pixel   - pixel mode.           |\033[49m\n"
            // "\033[47m|   eraser   - pixel eraser.         |\033[49m\n"
            "\033[47m|   save (w) - save current sketch.  |\033[49m\n"
            "\033[47m|   edit (e) - load saved data.      |\033[49m\n"
            "\033[47m|   quit (q) - quit GRAPPA.          |\033[49m\n"
            "\033[47m+------------------------------------+\033[49m\n");
    printf("\033[39m\n");
    fflush(stdout);
}

inline void Command::Notification(){
    char Command[100];
    sscanf(CommandString[CmdID],"%s",Command);
    printf("No such command. : '%s'\n",Command);
    fflush(stdout);
}

inline void Command::DrawCommand(){
    if(CMFLAG){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, windowW, windowH, 0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glColor3d(0.00,0.10,0.15);
        glBegin(GL_QUADS);
        glVertex2d(0,windowH-30);
        glVertex2d(windowW,windowH-30);
        glVertex2d(windowW,windowH);
        glVertex2d(0,windowH);
        glEnd();
        glColor3d(1,1,1);
        static char s[256];
        static unsigned char count = 0;
        static bool flag = false;
        if(flag){
            sprintf(s,":%s",CommandString[CmdID]);
            if(count%32==0) flag = false;
        }else{
            memset(s,'\0',sizeof(s));
            sprintf(s,":%s",CommandString[CmdID]);
            int size = strlen(s);
            memset(s+size-CmdCursor,'_',1);
            if(count%32==0) flag = true;
        }
        ++count;
        glDrawString2(s,5,windowH-10);

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
}


inline void Command::CommandMode(){
    if(CMFLAG) CMFLAG = false;
    else CMFLAG = true;
}


inline bool Command::CommandFlag(){
    return CMFLAG;
}


inline int Command::CommandStore(unsigned char key){
    static char s[4],tmp[128];
    int size = strlen(CommandString[CmdID]);
    if(CMFLAG){
        switch(key){
            case 127: // delete key
                if(0<size){
                    if(CmdCursor){
                        if(CmdCursor<size){
                            for(int i=size-CmdCursor;i<size;++i){
                                CommandString[CmdID][i-1] = CommandString[CmdID][i];
                            }
                            CommandString[CmdID][size-1] = '\0';
                        }
                    }
                    else memset(CommandString[CmdID]+size-1,'\0',1);
                }
                else{
                    HstCounter = 0;
                    CMFLAG = false;
                }
                break;

            case 13: // return key
                if(0<size){
                    if(HstCounter) HstCounter = 0;
                    if(CmdCursor)  CmdCursor  = 0;
                    ++CmdID;
                    if(CmdNum<=CmdID){
                        CmdID = 0;
                        memset(CommandString[CmdID],'\0',sizeof(CommandString[CmdID]));
                    }
                    CMFLAG = false;
                }
                break;

            default: // input charactor
                if(CmdCursor&&CmdCursor<=size&&size<32){
                    memset(tmp,'\0',sizeof(tmp));
                    for(int i=0;i<CmdCursor;++i)
                        tmp[i] = CommandString[CmdID][i+size-CmdCursor];
                    CommandString[CmdID][size-CmdCursor]   = key;
                    CommandString[CmdID][size-CmdCursor+1] = '\0';
                    strcat(CommandString[CmdID],tmp);
                }
                else{
                    sprintf(s,"%c",key);
                    if(size<32) strcat(CommandString[CmdID],s);
                }
                break;
        }
    }
    return size;
}


inline int Command::CommandHistory(int key){
    if(CMFLAG){
        switch(key){
            case GLUT_KEY_UP: //up-arrow key
                if(0<CmdID-HstCounter){
                    if(strlen(CommandString[CmdID-HstCounter-1])){
                        ++HstCounter;
                        strcpy(CommandString[CmdID],CommandString[CmdID-HstCounter]);
                    }
                }
                break;
            case GLUT_KEY_DOWN: //down-arrow key
                if(CmdID-HstCounter<CmdNum-1){
                    if(strlen(CommandString[CmdID-HstCounter+1])){
                        if(0<HstCounter) --HstCounter;
                        strcpy(CommandString[CmdID],CommandString[CmdID-HstCounter]);
                    }
                    if(HstCounter==0)
                        memset(CommandString[CmdID],'\0',sizeof(CommandString[CmdID]));
                }
                break;
            default:
                break;
        }
    }
    return strlen(CommandString[CmdID]);
}


inline void Command::CommandCursor(int key){
    if(CMFLAG){
        switch(key){
            case GLUT_KEY_RIGHT: //right-arrow key
                --CmdCursor;
                if(CmdCursor<0) CmdCursor = 0;
                break;
            case GLUT_KEY_LEFT: //left-arrow key
                ++CmdCursor;
                if((int)strlen(CommandString[CmdID])<CmdCursor)
                    CmdCursor = strlen(CommandString[CmdID]);
                break;
            default:
                break;
        }
    }
}


inline bool Command::RunCommand(const char *s0){
    bool match = false;
    if(!strcmp(CommandString[CmdID],s0)) match = true;
    if(match) printf("Command: %s\n",CommandString[CmdID]);
    return match;
}


inline bool Command::RunCommand(const char *s0, const char *s1){
    bool match = false;
    if(!strcmp(CommandString[CmdID],s0)) match = true;
    if(!strcmp(CommandString[CmdID],s1)) match = true;
    if(match) printf("Command: %s\n",CommandString[CmdID]);
    return match;
}


inline bool Command::RunCommand(const char *s0, const char *s1, const char *s2){
    bool match = false;
    if(!strcmp(CommandString[CmdID],s0)) match = true;
    if(!strcmp(CommandString[CmdID],s1)) match = true;
    if(!strcmp(CommandString[CmdID],s2)) match = true;
    if(match) printf("Command: %s\n",CommandString[CmdID]);
    return match;
}


inline bool Command::RunCommand(const char *s0, double *a1){
    bool match = false;
    char Command[100];
    double arg1 = 0.0;
    sscanf(CommandString[CmdID],"%s %lf",Command,&arg1);
    if(!strcmp(Command,s0)) match = true;
    if(match){
        (*a1) = arg1;
        printf("Command: %s\t%f\n",Command,(*a1));
    }
    return match;
}


inline bool Command::RunCommand(const char *s0, double *a1, double *a2){
    bool match = false;
    char Command[100];
    double arg1 = 0.0;
    double arg2 = 0.0;
    sscanf(CommandString[CmdID],"%s %lf %lf",Command,&arg1,&arg2);
    if(!strcmp(Command,s0)) match = true;
    if(match){
        (*a1) = arg1;
        (*a2) = arg2;
        printf("Command: %s\t%f\t%f\n",Command,(*a1),(*a2));
    }
    return match;
}


inline bool Command::RunCommand(const char *s0, double *a1, double *a2, double *a3){
    bool match = false;
    char Command[100];
    double arg1 = 0.0;
    double arg2 = 0.0;
    double arg3 = 0.0;
    sscanf(CommandString[CmdID],"%s %lf %lf %lf",Command,&arg1,&arg2,&arg3);
    if(!strcmp(Command,s0)) match = true;
    if(match){
        (*a1) = arg1;
        (*a2) = arg2;
        (*a3) = arg3;
        printf("Command: %s\t%f\t%f\t%f\n",Command,(*a1),(*a2),(*a3));
    }
    return match;
}


inline bool Command::RunCommand(const char *s0, double *a1, double *a2, double *a3, double *a4){
    bool match = false;
    char Command[100];
    double arg1 = 0.0;
    double arg2 = 0.0;
    double arg3 = 0.0;
    double arg4 = 0.0;
    sscanf(CommandString[CmdID],"%s %lf %lf %lf %lf",Command,&arg1,&arg2,&arg3,&arg4);
    if(!strcmp(Command,s0)) match = true;
    if(match){
        (*a1) = arg1;
        (*a2) = arg2;
        (*a3) = arg3;
        (*a4) = arg4;
        printf("Command: %s\t%f\t%f\t%f\t%f\n",Command,(*a1),(*a2),(*a3),(*a4));
    }
    return match;
}


inline bool Command::RunCommand(const char *s0, const char *s1, double *a1){
    char Command[100];
    double arg1 = 0.0;
    sscanf(CommandString[CmdID],"%s %lf",Command,&arg1);
    bool match = false;
    if(!strcmp(Command,s0)) match = true;
    if(!strcmp(Command,s1)) match = true;
    if(match){
        (*a1) = arg1;
        printf("Command: %s\t%f\n",Command,(*a1));
    }
    return match;
}


inline bool Command::RunCommandString(const char *s0, char *arg){
    static char Command[100];
    memset(arg,'\0',sizeof(*arg));
    sscanf(CommandString[CmdID],"%s %s",Command,arg);
    bool match = false;
    if(!strcmp(Command,s0)) match = true;
    if(match)
        printf("Command: %s\t'%s'\n",Command,arg);
    return match;
}


inline bool Command::RunCommandString(const char *s0, const char *s1, char *arg){
    static char Command[100];
    memset(arg,'\0',sizeof(*arg));
    sscanf(CommandString[CmdID],"%s %s",Command,arg);
    bool match = false;
    if(!strcmp(Command,s0)) match = true;
    if(!strcmp(Command,s1)) match = true;
    if(match)
        printf("Command: %s\t'%s'\n",Command,arg);
    return match;
}


/*****************************/
#endif //COMMAND_h_

