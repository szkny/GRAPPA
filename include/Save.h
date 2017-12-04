#include<stdio.h>
#include<stdlib.h>

#ifdef __APPLE__
#include<GL/freeglut.h>
#endif

#ifdef linux
#include<GL/glut.h>
#endif

#include<GRAPPA.h>

void Save();
void Load();
