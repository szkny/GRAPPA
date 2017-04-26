#ifndef MyGLUT_h_
#define MyGLUT_h_

/***************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/glut.h>

#include"define.h"

/* Polygon Mode */
bool PFLAG  =  true;    

/**************** Drawing Function ******************/

/* Drawing String Function (string,position x,position y) */
void glDrawString(const char *str, double x0, double y0){
	int size = strlen(str);
	glRasterPos2d(x0, y0);
	for(int i = 0; i < size; ++i){
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ic);
	}	
}


/* Drawing Small String Function (string,position x,position y) */
void glDrawString2(const char *str, double x0, double y0){
	int size = strlen(str);
	glRasterPos2d(x0, y0);
	for(int i = 0; i < size; ++i){
		char ic = str[i];
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, ic);
	}	
}


/* Draw Rectangular Function (length1,length2,length3,position-xyz) */
void glRectangular(double lx, double ly, double lz, double x, double y, double z){
	if(lx<=0||ly<=0||lz<=0){
		printf("error : the argument lx,ly,lz of glRectangular() must be positive.\n");
		exit(1);
	}
	glPushMatrix();
	glTranslated(x,y,z);
	GLdouble vertex[][3] = {       /*No.*/
		{-lx/2.0,-ly/2.0,-lz/2.0}, /* 0 */  
		{-lx/2.0, ly/2.0,-lz/2.0}, /* 1 */
		{ lx/2.0, ly/2.0,-lz/2.0}, /* 2 */
		{ lx/2.0,-ly/2.0,-lz/2.0}, /* 3 */
		{-lx/2.0,-ly/2.0, lz/2.0}, /* 4 */
		{-lx/2.0, ly/2.0, lz/2.0}, /* 5 */
		{ lx/2.0, ly/2.0, lz/2.0}, /* 6 */
		{ lx/2.0,-ly/2.0, lz/2.0}  /* 7 */
	};
	/* edge asign */
	int edge[][2] = {
		{  0, 1 },{  1, 2 },{  2, 3 },{  3, 0 },
		{  4, 5 },{  5, 6 },{  6, 7 },{  7, 4 },
		{  0, 4 },{  1, 5 },{  2, 6 },{  3, 7 }
	};
	/* face asign */
	int face[][4] = {
		{  0, 3, 2, 1 },
		{  0, 1, 5, 4 },
		{  1, 2, 6, 5 },
		{  2, 3, 7, 6 },
		{  0, 4, 7, 3 },
		{  4, 5, 6, 7 }
	};
	/* normal vector asign (for shadow) */
	GLdouble normal[][3] = {
		{ 0.0, 0.0,-1.0 },
		{-1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0,-1.0, 0.0 },
		{ 0.0, 0.0, 1.0 }
	};
	/* construction(lines) */
	if( PFLAG != true ){
		glBegin(GL_LINES);
		for(int i=0;i<12;++i){
			glVertex3dv(vertex[edge[i][0]]);
			glVertex3dv(vertex[edge[i][1]]);
		}
		glEnd();
	}
	else{ /* construction(polygon) */
		glBegin(GL_QUADS);
		for(int j=0;j<6;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
	}
	glPopMatrix();
}


/* Draw Hexagonal Prism Function (radius,length,position—xyz) */
void glHexagon(double r, double l, double x, double y, double z){
	
	if(r<=0||l<=0){
		printf("error : the argument r,l of glPentagon() must be positive.\n");
		exit(1);
	}
	glPushMatrix();
	glTranslated(x,y,z);
	
	const int N     =      6;
	const int array =  2*N+1;
	GLdouble vertex[array][3];
	for(int j=0;j<N;++j){
		vertex[j  ][0] =-l/2.0;
		vertex[j  ][1] = r*cos((2.0*PI*(double)j)/(double)N);
		vertex[j  ][2] = r*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+N][0] = l/2.0;
		vertex[j+N][1] = vertex[j][1];
		vertex[j+N][2] = vertex[j][2];
	}
	int face[N+1][4];
	for(int j=0;j<N-1;++j){
		face[j][0] = j    ;
		face[j][1] = j+N  ;
		face[j][2] = j+N+1;
		face[j][3] = j  +1;
	}
	face[N-1][0] =   N-1;
	face[N-1][1] = 2*N-1;
	face[N-1][2] =     N;
	face[N-1][3] =     0;
	GLdouble normal[N][3];
	for(int j=0;j<N;++j){
		normal[j][0] = 0.0;
		normal[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}
	if(PFLAG){
		glBegin(GL_QUADS);
		for(int j=0;j<N;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
	}
	if(PFLAG != true){
		double  x = -l/2.0;
		for(int i=0;i<2;++i){
			glBegin(GL_LINE_LOOP);
			for(int j=0;j<N;++j){
				double y = r*cos((2.0*PI*(double)j)/(double)N);
				double z = r*sin((2.0*PI*(double)j)/(double)N);
				glVertex3d(x,y,z);
			}
			glEnd();
			x=l/2.0;
		}
		int n = N;
		for(int i=0;i<n;++i){
			glBegin(GL_LINES);
			double y = r*cos((2.0*PI*(double)i)/(double)n);
			double z = r*sin((2.0*PI*(double)i)/(double)n);
			glVertex3d( l/2,y,z);
			glVertex3d(-l/2,y,z);
			glEnd();
		}
	}
	else{
		/* Lid of Prism */
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d( 1,0,0);
		for(int j=0;j<N;++j){
			double y = r*cos(-2.0*PI*(double)j/(double)N);
			double z = r*sin(-2.0*PI*(double)j/(double)N);
			glVertex3d(l/2.0,y,z);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(-1,0,0);
		for(int j=0;j<N;++j){
			double y = r*cos(2.0*PI*(double)j/(double)N);
			double z = r*sin(2.0*PI*(double)j/(double)N);
			glVertex3d(-l/2.0,y,z);
		}
		glEnd();
	}
	glPopMatrix();
}


/* Draw Cylinder Function (radius,length,position—xyz) */
void glCylinder(double r, double l, double x, double y, double z){
	if(r<=0||l<=0){
		printf("error : the argument r,l of glCylinder() must be positive.\n");
		exit(1);
	}
	glPushMatrix();
	glTranslated(x,y,z);
	
	const int N     = (r>2)?r*100:200; /* N-sided polygon */
	const int array =   2*N+1;
	GLdouble vertex[array][3];
	for(int j=0;j<N;++j){
		vertex[j  ][0] =-l/2.0;
		vertex[j  ][1] = r*cos((2.0*PI*(double)j)/(double)N);
		vertex[j  ][2] = r*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+N][0] = l/2.0;
		vertex[j+N][1] = vertex[j][1];
		vertex[j+N][2] = vertex[j][2];
	}
	int face[N+1][4];
	for(int j=0;j<N-1;++j){
		face[j][0] = j    ;
		face[j][1] = j+N  ;
		face[j][2] = j+N+1;
		face[j][3] = j  +1;
	}
	face[N-1][0] =   N-1;
	face[N-1][1] = 2*N-1;
	face[N-1][2] =     N;
	face[N-1][3] =     0;
	GLdouble normal[N][3];
	for(int j=0;j<N;++j){
		normal[j][0] = 0.0;
		normal[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}

	if(PFLAG){
		glBegin(GL_QUADS);
		for(int j=0;j<N;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
	}
	if(PFLAG != true){
		double  x = -l/2.0;
		double dl = 5.0;
		int Nl    = l/dl;
		for(int i=0;i<Nl+2;++i){
			glBegin(GL_LINE_LOOP);
			for(int j=0;j<N;++j){
				double y = r*cos((2.0*PI*(double)j)/(double)N);
				double z = r*sin((2.0*PI*(double)j)/(double)N);
				glVertex3d(x,y,z);
			}
			glEnd();
			x+=dl;
			if(x>l/2.0) x=l/2.0;
		}
		int n = 8;
		for(int i=0;i<n;++i){
			glBegin(GL_LINES);
			double y = r*cos((2.0*PI*(double)i)/(double)n);
			double z = r*sin((2.0*PI*(double)i)/(double)n);
			glVertex3d( l/2,y,z);
			glVertex3d(-l/2,y,z);
			glEnd();
		}
	}
	else{
		/* Lid of Cylinder */
		GLdouble normlid[][3] = {{1.0,0.0,0.0},{-1.0,0.0,0.0}};
		glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(normlid[0]);
		for(int j=0;j<N;++j){
			double y = r*sin(2.0*PI*(double)j/(double)N);
			double z = r*cos(2.0*PI*(double)j/(double)N);
			glVertex3d(l/2.0,y,z);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glNormal3dv(normlid[1]);
		for(int j=0;j<N;++j){
			double y = r*cos(2.0*PI*(double)j/(double)N);
			double z = r*sin(2.0*PI*(double)j/(double)N);
			glVertex3d(-l/2.0,y,z);
		}
		glEnd();
	}
	glPopMatrix();
}


/* Draw Pipe Function (radius,thickness,length,position—xyz) */
void glPipe(double r,double d, double l, double x, double y, double z){
	if(r<=0||d<=0||l<=0){
		printf("error : the argument r,d,l of glTube() must be positive.\n");
		exit(1);
	}
	else if(r<=d){
		printf("error : the argument r,d of glTube() must be r>d.\n");
		exit(1);
	}
	glPushMatrix();
	glTranslated(x,y,z);
	const int N     = (r>2)?r*50:100; /* N-sided polygon */
	const int array =   4*N+1;
	GLdouble vertex[array][3];
	for(int j=0;j<N;++j){
		vertex[j    ][0] =-l/2.0;
		vertex[j    ][1] = r*cos((2.0*PI*(double)j)/(double)N);
		vertex[j    ][2] = r*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+  N][0] = l/2.0;
		vertex[j+  N][1] = vertex[j][1];
		vertex[j+  N][2] = vertex[j][2];
		vertex[j+2*N][0] =-l/2.0;
		vertex[j+2*N][1] = (r-d)*cos((2.0*PI*(double)j)/(double)N);
		vertex[j+2*N][2] = (r-d)*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+3*N][0] = l/2.0;
		vertex[j+3*N][1] = vertex[j+2*N][1];
		vertex[j+3*N][2] = vertex[j+2*N][2];
	}
	int face1[N+1][4];
	for(int j=0;j<N-1;++j){
		face1[j][0] = j    ;
		face1[j][1] = j+N  ;
		face1[j][2] = j+N+1;
		face1[j][3] = j  +1;
	}
	face1[N-1][0] =   N-1;
	face1[N-1][1] = 2*N-1;
	face1[N-1][2] =   N+1;
	face1[N-1][3] =     1;
	int face2[N+1][4];
	for(int j=0;j<N-1;++j){
		face2[j][0] = j+2*N;
		face2[j][1] = j+2*N+1;
		face2[j][2] = j+3*N+1;
		face2[j][3] = j+3*N;
	}
	face2[N-1][0] = 3*N-1;
	face2[N-1][1] = 2*N+1;
	face2[N-1][2] = 3*N+1;
	face2[N-1][3] = 4*N-1;
	int face3[N+1][4];
	for(int j=0;j<N-1;++j){
		face3[j][0] = j;
		face3[j][1] = j+1;
		face3[j][2] = j+2*N+1;
		face3[j][3] = j+2*N;
	}
	face3[N-1][0] =   N-1;
	face3[N-1][1] =     0;
	face3[N-1][2] =   2*N;
	face3[N-1][3] = 3*N-1;
	int face4[N+1][4];
	for(int j=0;j<N-1;++j){
		face4[j][0] = j+N;
		face4[j][1] = j+3*N;
		face4[j][2] = j+3*N+1;
		face4[j][3] = j+N+1;
	}
	face4[N-1][0] = 2*N-1;
	face4[N-1][1] = 4*N-1;
	face4[N-1][2] =   3*N;
	face4[N-1][3] =     N;
	GLdouble normal1[N][3];
	for(int j=0;j<N;++j){
		normal1[j][0] = 0.0;
		normal1[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal1[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}
	GLdouble normal2[N][3];
	for(int j=0;j<N;++j){
		normal2[j][0] =-0.0;
		normal2[j][1] =-cos((2.0*PI*(double)j)/(double)N);
		normal2[j][2] =-sin((2.0*PI*(double)j)/(double)N);
	}
	if(PFLAG){
		glBegin(GL_QUADS);
		for(int j=0;j<N;++j){
			glNormal3dv(normal1[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face1[j][i]]);
			}
			glNormal3dv(normal2[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face2[j][i]]);
			}
			glNormal3d(-1,0,0);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face3[j][i]]);
			}
			glNormal3d( 1,0,0);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face4[j][i]]);
			}
		}
		glEnd();
	}
	else{
		double  x = -l/2.0;
		double dl = 5.0;
		int Nl    = l/dl;
		for(int i=0;i<Nl+2;++i){
			glBegin(GL_LINE_LOOP);
			for(int j=0;j<N;++j){
				double y = r*cos((2.0*PI*(double)j)/(double)N);
				double z = r*sin((2.0*PI*(double)j)/(double)N);
				glVertex3d(x,y,z);
			}
			glEnd();
			x+=dl;
			if(x>l/2.0) x=l/2.0;
		}
		int n = 4;
		for(int i=0;i<n;++i){
			glBegin(GL_LINES);
			double y = r*cos((2.0*PI*(double)i)/(double)n);
			double z = r*sin((2.0*PI*(double)i)/(double)n);
			glVertex3d( l/2,y,z);
			glVertex3d(-l/2,y,z);
			glEnd();
		}
		x = -l/2.0;
		for(int i=0;i<Nl+2;++i){
			glBegin(GL_LINE_LOOP);
			for(int j=0;j<N;++j){
				double y = (r-d)*cos((2.0*PI*(double)j)/(double)N);
				double z = (r-d)*sin((2.0*PI*(double)j)/(double)N);
				glVertex3d(x,y,z);
			}
			glEnd();
			x+=dl;
			if(x>l/2.0) x=l/2.0;
		}
		for(int i=0;i<n;++i){
			glBegin(GL_LINES);
			double y = (r-d)*cos((2.0*(double)i+1.0)*PI/(double)n);
			double z = (r-d)*sin((2.0*(double)i+1.0)*PI/(double)n);
			glVertex3d( l/2,y,z);
			glVertex3d(-l/2,y,z);
			glEnd();
		}
	}
	glPopMatrix();
}


/* Draw N-Side Polygon Prism Function (N,radius,length,position—xyz) */
void glPrism(const int N, double r, double l, double x, double y, double z){
	if(N<=0||r<=0||l<=0){
		printf("error : the argument (int)N,(double)r,(double)l of glPrism() must be positive.\n");
		exit(1);
	}
	glPushMatrix();
	glTranslated(x,y,z);
	
	const int array =  2*N+1;
	GLdouble vertex[array][3];
	for(int j=0;j<N;++j){
		vertex[j  ][0] =-l/2.0;
		vertex[j  ][1] = r*cos((2.0*PI*(double)j)/(double)N);
		vertex[j  ][2] = r*sin((2.0*PI*(double)j)/(double)N);
		vertex[j+N][0] = l/2.0;
		vertex[j+N][1] = vertex[j][1];
		vertex[j+N][2] = vertex[j][2];
	}
	int face[N+1][4];
	for(int j=0;j<N-1;++j){
		face[j][0] = j    ;
		face[j][1] = j+N  ;
		face[j][2] = j+N+1;
		face[j][3] = j  +1;
	}
	face[N-1][0] =   N-1;
	face[N-1][1] = 2*N-1;
	face[N-1][2] =     N;
	face[N-1][3] =     0;
	GLdouble normal[N][3];
	for(int j=0;j<N;++j){
		normal[j][0] = 0.0;
		normal[j][1] = cos((2.0*PI*(double)j)/(double)N);
		normal[j][2] = sin((2.0*PI*(double)j)/(double)N);
	}
	if(PFLAG){
		glBegin(GL_QUADS);
		for(int j=0;j<N;++j){
			glNormal3dv(normal[j]);
			for(int i=0;i<4;++i){
				glVertex3dv(vertex[face[j][i]]);
			}
		}
		glEnd();
	}
	if(PFLAG != true){
		double  x = -l/2.0;
		for(int i=0;i<2;++i){
			glBegin(GL_LINE_LOOP);
			for(int j=0;j<N;++j){
				double y = r*cos((2.0*PI*(double)j)/(double)N);
				double z = r*sin((2.0*PI*(double)j)/(double)N);
				glVertex3d(x,y,z);
			}
			glEnd();
			x=l/2.0;
		}
		int n = N;
		for(int i=0;i<n;++i){
			glBegin(GL_LINES);
			double y = r*cos((2.0*PI*(double)i)/(double)n);
			double z = r*sin((2.0*PI*(double)i)/(double)n);
			glVertex3d( l/2,y,z);
			glVertex3d(-l/2,y,z);
			glEnd();
		}
	}
	else{
		/* Lid of Prism */
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d( 1,0,0);
		for(int j=0;j<N;++j){
			double y = r*cos(-2.0*PI*(double)j/(double)N);
			double z = r*sin(-2.0*PI*(double)j/(double)N);
			glVertex3d(l/2.0,y,z);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glNormal3d(-1,0,0);
		for(int j=0;j<N;++j){
			double y = r*cos(2.0*PI*(double)j/(double)N);
			double z = r*sin(2.0*PI*(double)j/(double)N);
			glVertex3d(-l/2.0,y,z);
		}
		glEnd();
	}
	glPopMatrix();
}



/***************************/

#endif //"MyGLUT_h_"
