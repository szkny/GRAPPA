/*
 *  GRAPPA Commands Configurations
 */

#include<iostream>
#include<thread>
#include<exception>
#include<GRAPPA.h>
#include<Command.h>
#include<Save.h>

extern bool MFLAG; //defined in Mouse.cpp
extern GRAPPA  Gra;
extern Command Cmd;
extern const char *DefaultFileName;

void MouseDrawMode(void);
void KeyboardMode(void);
void KeyboardShortcut(unsigned char key, int x, int y);


void Commands(){
    static double Arg1,Arg2,Arg3;
    static char ArgString[200];

    if(Cmd.RunCommand("q","quit","exit"))
        exit(0);

    else if(Cmd.RunCommand("h","help"))
        Cmd.Help();

    else if(Cmd.RunCommand("undo"))
        Gra.Undo();

    else if(Cmd.RunCommand("redo"))
        Gra.Redo();

    else if(Cmd.RunCommand("status"))
        Gra.ShowStatus();

    else if(Cmd.RunCommand("reset","clear"))
        Gra.Reset();

    else if(Cmd.RunCommand("mv","move"))
        Gra.SetDrawMode(MLINEMOVE);

    else if(Cmd.RunCommand("cp","copy"))
        Gra.SetDrawMode(MLINECOPY);

    else if(Cmd.RunCommand("rot","rotate"))
        Gra.SetDrawMode(MLINEROTATE);

    else if(Cmd.RunCommand("co"))
        Gra.SetDrawMode(MCOLORBARLINE);

    else if(Cmd.RunCommand("co",&Arg1,&Arg2,&Arg3))
        Gra.SetDefaultLineColor(Arg1,Arg2,Arg3);

    else if(Cmd.RunCommand("cco"))
        Gra.SetDrawMode(MCOLORBARCANVAS);

    else if(Cmd.RunCommand("cco",&Arg1,&Arg2,&Arg3))
        Gra.SetCanvasColor(Arg1,Arg2,Arg3);

    else if(Cmd.RunCommand("lw","width",&Arg1))
        Gra.SetDefaultLineWidth(Arg1);

    else if(Cmd.RunCommand("p","pixel"))
        Gra.PixelMode();

    else if(Cmd.RunCommand("ps","pixelsize",&Arg1))
        Gra.SetPixelSize(Arg1);

    else if(Cmd.RunCommand("erase","eraser"))
        Gra.PixelEraser();

    else if(Cmd.RunCommand("free","freehand"))
        Gra.SetDrawMode(MFREEHAND);

    else if(Cmd.RunCommand("circle"))
        Gra.SetDrawMode(MCIRCLE);

    else if(Cmd.RunCommand("square"))
        Gra.SetDrawMode(MSQUARE);

    else if(Cmd.RunCommand("polygon",&Arg1))
        Gra.SetDrawMode(MPOLYGON,Arg1);

    else if(Cmd.RunCommand("line"))
        Gra.SetDrawMode(MSTRAIGHTLINE);

    else if(Cmd.RunCommand("rand","random"))
        Gra.SetDrawMode(MRANDOM);

    else if(Cmd.RunCommand("kaleido"))
        Gra.SetDrawMode(MKALEIDO);

    else if(Cmd.RunCommandString("w","save",ArgString))
        Save(ArgString);

    else if(Cmd.RunCommandString("e","edit",ArgString))
        Load(ArgString);

    else if(Cmd.RunCommandString("wq",ArgString)){
        Save(ArgString);
        exit(0);
    }

    else
        Cmd.Notification();

    fflush(stdout);
}


void InputKey(unsigned char key, int x, int y){
    if(key == 127){ //delete key
        int size = Cmd.CommandStore(key);
        if(size == 0) KeyboardMode();
    }
    else if(key == 13){ //return key
        Commands();
        Cmd.CommandStore(key);
        KeyboardMode();
    }
    else if(key == 9){ //tab key
        ;
    }
    else{
        Cmd.CommandStore(key);
    }
}


/* arrow key */
void keyboard_sp(int key, int x, int y){
    if(key==GLUT_KEY_UP||key==GLUT_KEY_DOWN)
        Cmd.CommandHistory(key);
    if(key==GLUT_KEY_RIGHT||key==GLUT_KEY_LEFT)
        Cmd.CommandCursor(key);
}

