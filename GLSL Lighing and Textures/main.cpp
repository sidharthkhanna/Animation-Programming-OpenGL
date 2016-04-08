//=============================================================================
// Sample Application for GLEW, and cwc Application/Window class using freeglut
// Sample Application using files from clockwork coders
// Modified by Ross Maciejewski 2014
//=============================================================================

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include <iostream>
#include "glsl.h"
#include "perlin.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


//-----------------------------------------------------------------------------

extern "C" unsigned char *stbi_load(char const *filename, int *x, int *y, int *comp, int req_comp);
int a=0;
float x=0.0;
float z=4.0;
float z2=-1;
float angle=0.0;
float x2=0.0;
	int a1=1;
	float f=0.3;

unsigned char *image1;

static int p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
static int start = 1;

typedef struct snowManNode
{
   GLfloat m[16];
   void (*f)();
     cwc::glShader *shader4;
   struct snowManNode *sibling;
   struct snowManNode *child;
} snowManNode;
snowManNode body_node, head_node1,head_node, button1_node, button2_node, button3_node, lefteye_node, righteye_node, nose_node,cap_node1,body_node1,cap_node;
// navigation up down bottom right
void navigationkeys(int key, int x1, int y1) {

		

	switch (key) {

		case GLUT_KEY_UP :

			x += x2 * f;
			z += z2 * f;
			break;

		 case GLUT_KEY_DOWN :
			

			x -= x2 * f;
			z -= z2 * f;
			break;
		case GLUT_KEY_LEFT :
			angle -= 0.2;

			x2 = sin(angle);
			z2 = -cos(angle);
			break;
       case GLUT_KEY_RIGHT :
			angle += 0.2;
			x2 = sin(angle);
			z2 = -cos(angle);
			break;
		
	}
	glutPostRedisplay();
}
GLUquadric* quadratic;
void sphere()   // body of snowman
{  
	 GLfloat material_Ka[] = {0.25, 0.25, 0.25, 1.0};
     GLfloat material_Kd[] = {0.4, 0.4, 0.4, 1.0};
     GLfloat material_Ks[] = {0.774597, 0.774597, 0.774597, 1.0};
     //GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 76.8;

	

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	
	
	
	quadratic = gluNewQuadric(); //Create a pointer to the quadric object
    gluQuadricNormals(quadratic, GLU_SMOOTH); //Create smooth normal
	gluQuadricTexture(quadratic, TRUE);
    gluSphere(quadratic, 0.4, 100, 100);
}	
void sphere1()  // head of snowman

{
	
	 GLfloat material_Ka[] = {0.329412, 0.223529, 0.027451, 1.0};
     GLfloat material_Kd[] = {0.780392, 0.568627, 0.113725, 1.0};
     GLfloat material_Ks[] = {0.992157, 0.941176, 0.807843, 1.0};
     GLfloat material_Ke[] = {0.1f, 0.0f, 0.0f, 0.0f};
     GLfloat material_Se = 27.8974;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
     glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
 
	quadratic = gluNewQuadric(); //Create a pointer to the quadric object
    gluQuadricNormals(quadratic, GLU_SMOOTH); //Create smooth normal
		gluQuadricTexture(quadratic, TRUE);
    gluSphere(quadratic, 0.3, 100, 100);
	

}
void sphere2() // eyes of snowman
{  
	
	 GLfloat material_Ka[] = {0.0, 0.0, 0.0, 1.0};
     GLfloat material_Kd[] = {0.01, 0.01, 0.01, 1.0};
     GLfloat material_Ks[] = {0.50, 0.50, 0.50, 1.0};

     GLfloat material_Se = 32.0;

	

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
 
	 
    
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
	quadratic = gluNewQuadric(); //Create a pointer to the quadric object
    gluQuadricNormals(quadratic, GLU_SMOOTH); //Create smooth normal
    gluSphere(quadratic, 0.03, 100, 100);
	

}

void sphere3() // buttons of snowman
{  
	
	 GLfloat material_Ka[] = {0.05375, 0.05, 0.06625, 0.82};
     GLfloat material_Kd[] = {0.18275, 0.17, 0.22525, 0.82};
     GLfloat material_Ks[] = {0.332741, 0.328634, 0.346435, 0.82};

     GLfloat material_Se = 38.4;

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
 
	 
    
     glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
	quadratic = gluNewQuadric(); //Create a pointer to the quadric object
    gluQuadricNormals(quadratic, GLU_SMOOTH); //Create smooth normal
    gluSphere(quadratic, 0.03, 100, 100);
	

}

void cap() // cap of snowman
{  
	GLfloat material_Ka[] = {0.24725, 0.2245, 0.0645, 1.0};
     GLfloat material_Kd[] = {0.34615, 0.3143, 0.0903, 1.0};
     GLfloat material_Ks[] = {0.797357, 0.723991, 0.208006, 1.0};
   
     GLfloat material_Se = 83.2;
	 
	

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	 quadratic = gluNewQuadric(); //Create a pointer to the quadric object
    gluQuadricNormals(quadratic, GLU_SMOOTH); //Create smooth normal
		gluQuadricTexture(quadratic, TRUE);
		  gluCylinder(quadratic,0.2,0,0.5,100,100);
  
}

void nose() // nose of snowman
{  	GLfloat material_Ka[] = {0.105882, 0.058824, 0.113725, 1.0};
     GLfloat material_Kd[] = {0.427451, 0.470588, 0.541176,  1.0};
     GLfloat material_Ks[] = {0.333333, 0.333333, 0.521569,  1.0};
   
     GLfloat material_Se = 9.84615;
	  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glutSolidCone(0.03,1,100,100);
}



class myWindow : public cwc::glutWindow
{
protected:
   cwc::glShaderManager SM;
   cwc::glShader *shader;
   cwc::glShader *shader1;
   cwc::glShader *shader2;
   cwc::glShader *shader3;
    cwc::glShader *shader5;
	 cwc::glShader *shader6;





protected: 
	int scene;

	//Ross: Some variables I created for texturing
	unsigned char *image;
	int imageWidth;
	int imageHeight;
	int bitDepth;
	GLuint texture;
	

public:
	myWindow(){}

	virtual void OnRender(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Ross:  This is where I draw things.  I have three different scene examples.
		switch(scene)
		{
			case 1:
				a1=1;
			
				DemoTexture();
			   figure1();
			   figure();
			   Scene1();
				
				break;
			case 2:
			    a1=0;
			 DemoTexture();
			   figure1();
			  
				Scene2();
		        break;
			case 3:
				a1=2;
				DemoTexture();
				figure1();
				Scene3();
				break;
		}
		
		glutSwapBuffers();
	}

	
// Snowman1 mode

	void figure1()

{

	glLoadIdentity();
	
	
	
	glPushMatrix();
	glTranslatef(-0.4,-0.6,0.0);
	//body
	glGetFloatv(GL_MODELVIEW_MATRIX, body_node1.m);

	body_node1.child = &head_node1;




	body_node1.sibling = NULL;
	

	

	body_node1.f = sphere;
	if(a1==1 || a1==2 )
	body_node1.shader4=shader1;
	else 
    body_node1.shader4=shader5;
	
	

	
	
	head_node1.child = &cap_node1;

	head_node1.sibling = &button1_node;
	cap_node1.sibling = &lefteye_node;
	lefteye_node.sibling = &righteye_node;
	righteye_node.sibling = &nose_node;
	button1_node.sibling = &button2_node;
	button2_node.sibling = &button3_node;

	glPopMatrix();
	glPushMatrix();
	
	// head
	
	glTranslatef(0, 0.6, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node1.m);
	head_node1.f = sphere1;
	if(a1==1 || a1==2)
	head_node1.shader4=shader1;
	else 
		head_node1.shader4=shader5;
	

	glPopMatrix();
	glPushMatrix();
	//cap
	glTranslatef(0, 0.25, 0);
	 glRotatef(-90, 1, 0, 0);
	
	
	glGetFloatv(GL_MODELVIEW_MATRIX, cap_node1.m);
	cap_node1.f = cap;
	if(a1==1)
	cap_node1.shader4=shader1;
	else if(a1==0)
		cap_node1.shader4=shader5;
	else
		cap_node1.shader4=shader6;
	glPopMatrix();
	glPushMatrix();
	// left eye
	glTranslatef(-0.1, 0.1, 0.3);
	
	
	glGetFloatv(GL_MODELVIEW_MATRIX, lefteye_node.m);
	lefteye_node.f = sphere2;
	if(a1==1 || a1==2)
	lefteye_node.shader4=shader1;
	else
    lefteye_node.shader4=shader5;
	glPopMatrix();
	glPushMatrix();

	//right eye
	glTranslatef(0.1, 0.1, 0.3);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, righteye_node.m);
	righteye_node.f = sphere2;
	if(a1==1 || a1==2)
	righteye_node.shader4=shader1;
	else
			righteye_node.shader4=shader5;

	

	glPopMatrix();
	glPushMatrix();
	
	//nose

	glTranslatef(0.0, 0.0, 0.4);
	glRotatef(5, 1, 1, 1);

	glGetFloatv(GL_MODELVIEW_MATRIX, nose_node.m);
	nose_node.f = nose;
	if(a1==1 ||a1==2)
	righteye_node.shader4=shader1;
	else
		righteye_node.shader4=shader5;
	glPopMatrix();
	glPushMatrix();

	//button1
	glTranslatef(0.0, 0.15, 0.4);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, button1_node.m);
	button1_node.f = sphere3;
	if(a1==1 ||a1==2)

	button1_node.shader4=shader1;
	else
		button1_node.shader4=shader5;

	glPopMatrix();
	glPushMatrix();

	//button2
	glTranslatef(0.0, -0.05, 0.4);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, button2_node.m);
	button2_node.f = sphere3;
	if(a1==1 ||a1==2)
	button2_node.shader4=shader1;
	else
    	button2_node.shader4=shader5;
	glPopMatrix();
	glPushMatrix();

	//button3
	glTranslatef(0.0, -0.25, 0.4);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, button3_node.m);
	button3_node.f = sphere3;
	if(a1==1 ||a1==2)
	button3_node.shader4=shader1;
	else
    button3_node.shader4=shader5;
	glPopMatrix();
	
}

// Snowman2
	void figure()

{

	glLoadIdentity();
	
	glPushMatrix();
	//body

	glTranslatef(0.1,-0.6,0.0);
		glRotatef(90,1,0,0);
			
	

	glGetFloatv(GL_MODELVIEW_MATRIX, body_node.m);
    body_node.child = &head_node;
    body_node.f = sphere;
	body_node.shader4=shader2;
    head_node.child = &cap_node;
	glRotatef(-90,1,0,0);
	
	

	
	glPopMatrix();
	
	
	glPushMatrix();

	//head

	glTranslatef(0.0,0.0,-0.6);
	
	glRotatef(100,0,0,1);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = sphere1;
	head_node.shader4=shader;
	
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	glTranslatef(0.0, 0.0, 0.25);
	 
	//cap
	
	glGetFloatv(GL_MODELVIEW_MATRIX, cap_node.m);
	cap_node.f = cap;
	cap_node.shader4=shader2;
	glPopMatrix();
	
}

// traverse to render snowman1 and 2
void traverse(snowManNode *root)
{
	if (root == NULL) return;
	glPushMatrix();
	glMultMatrixf(root->m);

	 if (root->shader4)root->shader4->begin();


	root->f();

	 if (root->shader4)root->shader4->end();
	if (root->child != NULL)
	
		traverse(root->child);
	glPopMatrix();
	if (root->sibling != NULL)
		traverse(root->sibling);

}
/* Coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */





double noise1(double arg)
{
   int bx0, bx1;
   double rx0, rx1, sx, t, u, v, vec[1];

   vec[0] = arg;
   if (start) {
      start = 0;
      init();
	  printf("here-init?\n");
   }

   printf("here?\n");

   setup(0,bx0,bx1,rx0,rx1);

   sx = s_curve(rx0);
   u = rx0 * g1[ p[ bx0 ] ];
   v = rx1 * g1[ p[ bx1 ] ];

   return(lerp(sx, u, v));
}

double noise2(double vec[2])
{
   int bx0, bx1, by0, by1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
   int i, j;

   if (start) {
      start = 0;
      init();
   }

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);

   i = p[ bx0 ];
   j = p[ bx1 ];

   b00 = p[ i + by0 ];
   b10 = p[ j + by0 ];
   b01 = p[ i + by1 ];
   b11 = p[ j + by1 ];

   sx = s_curve(rx0);
   sy = s_curve(ry0);

   q = g2[ b00 ] ; u = at2(rx0,ry0);
   q = g2[ b10 ] ; v = at2(rx1,ry0);
   a = lerp(sx, u, v);

   q = g2[ b01 ] ; u = at2(rx0,ry1);
   q = g2[ b11 ] ; v = at2(rx1,ry1);
   b = lerp(sx, u, v);

   return lerp(sy, a, b);
}

double noise3(double vec[3])
{
   int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
   double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
   int i, j;

   if (start) {
      start = 0;
      init();
   }

   setup(0, bx0,bx1, rx0,rx1);
   setup(1, by0,by1, ry0,ry1);
   setup(2, bz0,bz1, rz0,rz1);

   i = p[ bx0 ];
   j = p[ bx1 ];

   b00 = p[ i + by0 ];
   b10 = p[ j + by0 ];
   b01 = p[ i + by1 ];
   b11 = p[ j + by1 ];

   t  = s_curve(rx0);
   sy = s_curve(ry0);
   sz = s_curve(rz0);

   q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
   q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
   a = lerp(t, u, v);

   q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
   q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
   b = lerp(t, u, v);

   c = lerp(sy, a, b);

   q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
   q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
   a = lerp(t, u, v);

   q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
   q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
   b = lerp(t, u, v);

   d = lerp(sy, a, b);

   return lerp(sz, c, d);
}

void normalize2(double v[2])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
}

void normalize3(double v[3])
{
   double s;

   s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] = v[0] / s;
   v[1] = v[1] / s;
   v[2] = v[2] / s;
}

void init(void)
{
   int i, j, k;

   for (i = 0 ; i < B ; i++) {
      p[i] = i;
      g1[i] = (double)((rand() % (B + B)) - B) / B;

      for (j = 0 ; j < 2 ; j++)
         g2[i][j] = (double)((rand() % (B + B)) - B) / B;
      normalize2(g2[i]);

      for (j = 0 ; j < 3 ; j++)
         g3[i][j] = (double)((rand() % (B + B)) - B) / B;
      normalize3(g3[i]);
   }

   while (--i) {
      k = p[i];
      p[i] = p[j = rand() % B];
      p[j] = k;
   }

   for (i = 0 ; i < B + 2 ; i++) {
      p[B + i] = p[i];
      g1[B + i] = g1[i];
      for (j = 0 ; j < 2 ; j++)
         g2[B + i][j] = g2[i][j];
      for (j = 0 ; j < 3 ; j++)
         g3[B + i][j] = g3[i][j];
   }
}

/* --- My harmonic summing functions - PDB --------------------------*/

/*
   In what follows "alpha" is the weight when the sum is formed.
   Typically it is 2, As this approaches 1 the function is noisier.
   "beta" is the harmonic scaling/spacing, typically 2.
*/

double PerlinNoise1D(double x,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p,scale = 1;

   p = x;
   for (i=0;i<n;i++) {
      val = noise1(p);
      sum += val / scale;
      scale *= alpha;
      p *= beta;
   }
   return(sum);
}

double PerlinNoise2D(double x,double y,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p[2],scale = 1;

   p[0] = x;
   p[1] = y;
   for (i=0;i<n;i++) {
      val = noise2(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
   }
   return(sum);
}

double PerlinNoise3D(double x,double y,double z,double alpha,double beta,int n)
{
   int i;
   double val,sum = 0;
   double p[3],scale = 1;

   p[0] = x;
   p[1] = y;
   p[2] = z;
   for (i=0;i<n;i++) {
      val = noise3(p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
      p[2] *= beta;
   }
   return(sum);
}

// plane for snowman
void plane()
{
 glBegin(GL_QUADS);                
      

		GLfloat material_Ka[] = {0.25, 0.20725, 0.20725, 0.922};
     GLfloat material_Kd[] = {1.0, 0.829, 0.829, 0.922};
     GLfloat material_Ks[] = {0.296648, 0.296648, 0.296648, 0.922};
    
     GLfloat material_Se = 11.264;

	

     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	 glTexCoord2f(0,0);
      glVertex3f( -1.0f, -1.0f,  1.0f);
	  glTexCoord2f(1,0);

      glVertex3f(1.0f, -1.0f,  1.0f);
	    glTexCoord2f(1,1);
      glVertex3f(1.0f, -1.0f, -1.0f);
	      glTexCoord2f(0,1);
      glVertex3f( -1.0f, -1.0f, -1.0f);
	  glEnd();
	  


}
// Scene 1 has snowman1 and snowman2
	void Scene1(void)
	{
		glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
		gluPerspective(45,1,1,100);
		
		
	
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	 

 gluLookAt(	x, 0.0f, z,
			x+x2, 0.0f,  z+z2,
			0.0f, 1.0f,  0.0f);
     
 
  
     if (shader3) shader3->begin();

 plane();
     if (shader3) shader3->end();
   
			glBindTexture(GL_TEXTURE_2D, this->texture);
	
		
			traverse(&body_node1);
			glTranslatef(0.4,0,0);
			traverse(&body_node);
		
		
	

	}

	
// Scene 3 has bump hat for snowman1
	void Scene3(void)
	{
		glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	
       gluPerspective(45,1,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	 gluLookAt(	x, 0.0f, z,
			x+x2, 0.0f,  z+z2,
			0.0f, 1.0f,  0.0f);
	
			//Essentially I need to tell the shader what texture to use
			glBindTexture(GL_TEXTURE_2D, this->texture);
			
			traverse(&body_node1);
			
		
	}
	// Scene2 has marble snowman
	void Scene2(void)
	{
		glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	
       gluPerspective(45,1,1,100);
	   glMatrixMode(GL_MODELVIEW);
	   glLoadIdentity();
	   
 gluLookAt(	x, 0.0f, z,
			x+x2, 0.0f,  z+z2,
			0.0f, 1.0f,  0.0f);
	
	   if (shader5) shader5->begin();
			//Essentially I need to tell the shader what texture to use
			glBindTexture(GL_TEXTURE_2D, this->texture);
	 traverse(&body_node1);
	   if (shader5) shader5->end();

	}
	

	
	


	virtual void OnIdle() {}

	// When OnInit is called, a render context (in this case GLUT-Window) 
	// is already available!

	
	virtual void OnInit()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
	
		//Ross: Here is where I declare some variables you need for textures (not scene, that's for changing the scene)
		this->scene = 1;
		this->imageWidth = 128;
		this->imageHeight = 128;
		this->bitDepth = 24;

		//Ross:  This is where I set up the lights
	figure(); // snowman2
	figure1();// snowman1
	    DemoLight();
		DemoTexture();
	
		//figure1();
		
	//Ross:  This is where I set up the textures
	

		//Ross: The GLSL loaders initialization is already handled by the CWC files linked.
		//If you change the name of your shader you would need to modify here
		shader = SM.loadfromFile("vertexshader.txt","fragmentshader.txt"); // load (and compile, link) from file
		  if (shader==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		  shader3 = SM.loadfromFile("vertexshader.txt","fragmentshader3.txt"); // load (and compile, link) from file
		  if (shader3==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		  	shader1 = SM.loadfromFile("vertexshader.txt","fragmentshader1.txt"); // load (and compile, link) from file
		  if (shader1==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		  	shader2 = SM.loadfromFile("vertexshader.txt","fragmentshader2.txt"); // load (and compile, link) from file
		  if (shader2==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		  shader5 = SM.loadfromFile("vertexshader.txt","fragmentshader5.txt"); // load (and compile, link) from file
		  if (shader5==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		   shader6 = SM.loadfromFile("vertexshader2.txt","fragmentshader6.txt"); // load (and compile, link) from file
		  if (shader6==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";
		   

	}

	//Ross: Callbacks for most everything you need
	virtual void OnResize(int w, int h) {}
	virtual void OnClose(void){}
	virtual void OnMouseDown(int button, int x, int y) {}    
	virtual void OnMouseUp(int button, int x, int y) {}
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}

	//Ross: This should be obvious, but these are the keyboard listeners
	virtual void OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close Window!
		} 

		if(cAscii == '1')
		{   
			this->scene = 1;
			
		}
		if(cAscii == '2')
		{
			this->scene = 2;
		

		}
		if(cAscii == '3')
			this->scene = 3;
		if(cAscii == '4')
			this->scene = 4;

		glutPostRedisplay();
	};

	virtual void OnKeyUp(int nKey, char cAscii)
	{
		if (cAscii == 'f')
		{
			SetFullscreen(true);
		}
		else if (cAscii == 'w')
		{
			SetFullscreen(false);
		}
	};

	//Ross: This is where I set up all the textures
	void DemoTexture(void)
	{
		/* Load in a PNG image */
		int loadCorrectly = 0;
		//Use the stbi_image file to load an image
		if(a1==1)
		image = stbi_load("sidharth.jpg", &this->imageWidth, &this->imageHeight, &this->bitDepth, 0);

		else if(a1==0)
		
		image = noisefunction1();

 	else 
	{
		
   image = stbi_load("bumps.jpg", &this->imageWidth, &this->imageHeight, &this->bitDepth, 0);
		}

		glGenTextures(1, &this->texture); //generate the texture with the loaded data

		//The first thing that must take place in the process of uploading the texture is a call to glBindTexture. 
		//What glBindTexture does is it tells OpenGL which texture "id" we will be working with. 
		//A texture "id" is just a number that you will use to access your textures. Here is a sample call.
		glBindTexture(GL_TEXTURE_2D, texture); //bind texture to its array


		//The glPixelStorei call tells OpenGL how the data that is going to be uploaded is aligned. 
		//This call tells OpenGL that the pixel data which is going to be passed to it is aligned in byte order, 
		//this means that the data has one byte for each component, one for red, green and blue
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
		//The glTexEnvf call sets environment variables for the current texture. 
		//What this does is tell OpenGL how the texture will act when it is rendered into a scene.
		//What this does is sets the active texture to GL_MODULATE. 
		//The GL_MODULATE attribute allows you to apply effects such as lighting and coloring to your texture. 
		//If you do not want lighting and coloring to effect your texture and you would like to display the texture unchanged when 
		//coloring is applied replace GL_MODULATE with GL_DECAL.
		//This is not needed if you use shaders!!
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		//The glTexImage2D call is our goal. 
		//This call will upload the texture to the video memory where it will be ready for us to use in our programs. 
		//I am going to explain this call parameter by parameter since it is so important to what we are doing.
		//target - The target of this call, it will always be GL_TEXTURE_2D.
		//level - The level of detail number, this should be left at 0 for our purposes. 
			//Once you become more adept at OpenGL texture mapping this parameter will be something that you might change.
		//internalformat - Internal components parameter. 
			//This tells OpenGL how many color components to represent internally from the texture that is uploaded. 
			//There are many symbolic constants for this parameter but the one which is most widely used is GL_RGB; this constant is equal to 3.
		//width & height - The width and height of the image data. These must be integers that are equal to 2n+2(border) for some integer n.
			//What this basically means is that the texture width and height must be a power of two (2,4,8,16,32,63,128,256,512, etc).
		//border - Image border, must be 0 or 1. I always use 0 in my code since I do not use image borders.
		//format - Format of the pixel data that will be uploaded. There are many constants which are accepted but GL_RGB is the value that is widely used.
		//type - Type of data that will be uploaded. Again there are several symbolic constants but the one which I use is GL_UNSIGNED_BYTE.
		//pixels - Pointer to the image data. 
			//This is the image data that will be uploaded to the video memory. 
			//Note that after your call to glTexImage2D you can free this memory since the texture is already uploaded into video memory.
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glEnable (GL_TEXTURE_2D);
	}

	//Marble function perlin noise
	unsigned char* noisefunction1()
	{  unsigned char *texture;
	 texture=new unsigned char[imageWidth*imageHeight*3];
		for(double i=0;i<imageWidth;i++)
		{
			for(double j=0;j<imageHeight;j++)
			{
			double x=i/imageWidth;
			double y = j/imageHeight;
			double beta =2;
			double alpha=1.5;
			int N1=6;
			
				double value=PerlinNoise2D(x,y,alpha,beta,N1);
				
				value=abs(value*255);
								
				
				texture[(int(i+j*imageWidth)*3)]=value;
				texture[(int(i+j*imageWidth)*3)+1]=value;
				texture[(int(i+j*imageWidth)*3)+2]=value;

			}
		}
		return texture;
		}


   //Ross: This is where I set up the lights
   void DemoLight(void)
   {
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
	 
     
     // Light model parameters:
     // -------------------------------------------
     
     GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
     
     glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
     glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
     
     // -------------------------------------------
     // Spotlight Attenuation
     
     GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
     GLint spot_exponent = 30;
     GLint spot_cutoff = 180;
     
     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
     glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
     glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    
     GLfloat Kc = 1.0;
     GLfloat Kl = 0.0;
     GLfloat Kq = 0.0;
     
     glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
     glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
     
     
     // ------------------------------------------- 
     // Lighting parameters:

     GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
     GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
     GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
     GLfloat light_Ks[]  = {1.0f, 1.0f, 1.0f, 1.0f};

     glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
     glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

     // -------------------------------------------
     // Material parameters:

   }

  
};

//-----------------------------------------------------------------------------
class myApplication : public cwc::glApplication
{
public:
	//Ross: Here is a simple output for checking that things are working
	virtual void OnInit() {std::cout << "Hello !\n"; }
};

//-----------------------------------------------------------------------------




int main(void)
{
	myApplication*  pApp = new myApplication;
	myWindow* myWin = new myWindow();
	glutSpecialFunc(navigationkeys);

	pApp->run();
	delete pApp;
	return 0;
}

//-----------------------------------------------------------------------------

