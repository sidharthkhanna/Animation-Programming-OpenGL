
/* Assignment 1 
 * 
 * A basic, first OpenGL program.
 * 
 * This program illustrates how you open an window, specify its position and size,
 * and draw something in the window.
 *
 * Also illustrated: the state-machine operation of OGL. 
 *
 * When you resize the window so it is not square, the box changes shape. This might
 * not be desired -- we will look into fixing this later. (Keep in mind, this has
 * something to do with the aspect ratio.)
 *
 * Try changing the size of gluOrtho2D -- see in code below -- and you'll see how the
 * relative size of the box changes within the window.
 *
 *
 * Dianne Hansford, August 2004
 * Modified by Ross Maciejewski August 2011
 */

#include <windows.h>
#include <ole2.h>
#include <ocidl.h>
#include <olectl.h>
#include <gl/gl.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include<time.h>



/* Include the GLUT library. This file (glut.h) contains gl.h and glu.h */
/* See how this is "glut.h" as opposed to <glut.h> - this is due to the fact that you need
   glut in your local directory. */
#include "glut.h"

// Structure for hierarchical StickMan in Assignment 2, this is only a starting point for the hierarchical structure
// You may need other items here or less items
typedef struct stickManNode
{
   GLfloat m[16];
   void (*f)();
   struct stickManNode *sibling;
   struct stickManNode *child;
} stickManNode;
stickManNode torso_node,torso_node1,torso_node2, head_node, larm_node, rarm_node, luleg_node, ruleg_node, llleg_node, rlleg_node;

 



/* These are the variables used to define the images being used in the example, you may need to redefine your own widths and heights */
unsigned char *image;
unsigned char Red, Green, Blue;
int imageWidth = 500;
int imageHeight = 375;
BOOL squarevisible = FALSE;
BOOL circlevisible = FALSE;
BOOL Testvisible = TRUE;
BOOL image1visible = FALSE;
int stickman = 0;
float X, Y;
BOOL colorvisible = FALSE;
int defaultstick = 0;
int walkingstick = 0;
BOOL color1visible = FALSE;
float angle = 0;
float angle1 = 0;
float angle2 = 0;
float translatex = 0;
int stick = 0;
int count = 0;
float sq[3][2];
clock_t t1, t2;
int a1 = 0;
int a = 0;
const float DEG2RAD = 3.14159 / 180.;
long elapsed;
long elapsed1;
long elapsed2;





/* We will have lots of angle calculations in class, this converts degrees to radians PI/180 */


// You may have lots of global variables to control states and animation, these would go below here

//You are REQUIRED to modularize your programs!  Here you see I've created a function stub to draw a unit circle outline (NOT FILLED)


void drawCircle1()
{

	float r = 0.1;
	glBegin(GL_POINTS);
	for ( double i = 1; i <= 360; i++)
	{
		glVertex2f(r*cos(i), r*sin(i));
	}
	
	glEnd();

}



void head()
{
	drawCircle1();
}
//An example function which draws a filled unit square (1x1) 
void drawSquare()
{
	glBegin(GL_POLYGON);
	
		glVertex2f(-.34, -.46);
		glVertex2f(.0545, -.75);
		glVertex2f( 0.23 ,-.34);
		glVertex2f(-.16, -.03);
		
	glEnd();

}

void drawSquare1()
{
	glBegin(GL_POLYGON);
	
		
	glVertex2f(-.604, -.63);
	glVertex2f(0.399,-.63);
	glVertex2f(0.399, .397);
	glVertex2f(-.604, .397);

	glEnd();

}


//An example function which draws a unit line (length 1)
void drawLine()
{
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(0,-0.3);
	glEnd();
}
void drawLine1()
{
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0,-0.2);
	glEnd();
}
void torso()
{
	drawLine();
}


//GRADUATE STUDENTS: You need to fill out this function to flip the image
void flipImag(unsigned char *image, unsigned char *flippedImage)
{
	for (int r = 0; r < 375; r++)
	{

		for (int j = 0; j < 500; j++)
		{
			 
			flippedImage[3 * ((375 - r) * 500 + j)] = image[3 * (r * 500 + j)];
			flippedImage[3 * ((375 - r) * 500 + j)+1] = image[3 * (r * 500 + j)+1];
			flippedImage[3 * ((375 - r) * 500 + j)+2] = image[3 * (r * 500 + j)+2];







		}
	}

}
	
void traverse(stickManNode *root)
{
	if (root == NULL) return;
	glPushMatrix();
	glMultMatrixf(root->m);
	root->f();
	if (root->child != NULL)
		traverse(root->child);
	glPopMatrix();
	if (root->sibling != NULL)
		traverse(root->sibling);

}
		 
void loadPNG(char* filename, int width, int height, int bitdepth)
{
	image = stbi_load(filename, &width, &height, &bitdepth, 0);
}

// default stickman mode
void figure1()

{
	glLoadIdentity();
	glPushMatrix();

	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);
	torso_node.child = &head_node;
    torso_node.sibling = NULL;
    torso_node.f = torso;


	
	


	head_node.sibling = &larm_node;
	head_node.child = NULL;
	larm_node.sibling = &rarm_node;
	larm_node.child = NULL;
	rarm_node.sibling = &ruleg_node;
	rarm_node.child = NULL;
	ruleg_node.sibling = &luleg_node;



	luleg_node.child = &llleg_node;
	ruleg_node.child = &rlleg_node;

	glTranslatef(0, 0.1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = head;

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.1, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-angle1, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, larm_node.m);
	larm_node.f = drawLine1;

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -0.1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(angle1, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, rarm_node.m);
	rarm_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();


	glTranslatef(0, -0.3, 0);
	glRotatef(45, 0, 0, 1);

	glGetFloatv(GL_MODELVIEW_MATRIX, ruleg_node.m);
	ruleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.3, 0);
	glRotatef(-45, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, luleg_node.m);
	luleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glRotatef(45, 0, 0, 1);
	glRotatef(angle, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, llleg_node.m);
	llleg_node.f = drawLine1;


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(-angle, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, rlleg_node.m);
	rlleg_node.f = drawLine1;
	glPopMatrix();
}
// normal stickman mode
void figure()

{
	glLoadIdentity();
	glPushMatrix();

	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);

	torso_node.child = &head_node;




	torso_node.sibling = NULL;


	torso_node.f = torso;


	
	


	head_node.sibling = &larm_node;
	head_node.child = NULL;
	larm_node.sibling = &rarm_node;
	larm_node.child = NULL;
	rarm_node.sibling = &ruleg_node;
	rarm_node.child = NULL;
	ruleg_node.sibling = &luleg_node;



	luleg_node.child = &llleg_node;
	ruleg_node.child = &rlleg_node;

	glTranslatef(0, 0.1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = head;

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.1, 0);
	glRotatef(-90, 0, 0, 1);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, larm_node.m);
	larm_node.f = drawLine1;

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -0.1, 0);
	glRotatef(90, 0, 0, 1);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, rarm_node.m);
	rarm_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();


	glTranslatef(0, -0.3, 0);
	glRotatef(45, 0, 0, 1);

	glGetFloatv(GL_MODELVIEW_MATRIX, ruleg_node.m);
	ruleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.3, 0);
	glRotatef(-45, 0, 0, 1);
	glGetFloatv(GL_MODELVIEW_MATRIX, luleg_node.m);
	luleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glRotatef(45, 0, 0, 1);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, llleg_node.m);
	llleg_node.f = drawLine1;


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	glRotatef(-45, 0, 0, 1);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, rlleg_node.m);
	rlleg_node.f = drawLine1;
	glPopMatrix();
}
// walking stickman mode
void figure2()

{
	glLoadIdentity();
	
	glPushMatrix();
	if (a1 == 0)
	{

		glTranslatef(translatex - 0.8, -0.30, 0);
	}
	if (a1 == 1)
	{
		glRotatef(-30, 0, 0, 1);
		glTranslatef(translatex-0.7 ,0.06, 0);
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, torso_node.m);




	torso_node.f = torso;
	

	torso_node.child = &head_node;
	



	torso_node.sibling = NULL;
	


	head_node.sibling = &larm_node;
	head_node.child = NULL;
	larm_node.sibling = &rarm_node;
	larm_node.child = NULL;
	rarm_node.sibling = &ruleg_node;
	rarm_node.child = NULL;
	ruleg_node.sibling = &luleg_node;
	

	
	luleg_node.child = &llleg_node;
	ruleg_node.child = &rlleg_node;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0.1, 0);
	glGetFloatv(GL_MODELVIEW_MATRIX, head_node.m);
	head_node.f = head;

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.1, 0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(angle2, 0, 0, 1);

	
	glGetFloatv(GL_MODELVIEW_MATRIX, larm_node.m);
	larm_node.f = drawLine1;

	glPopMatrix();
	glPushMatrix();

	glTranslatef(0, -0.1, 0);
	glRotatef(90, 0, 0, 1);
	glRotatef(-angle2, 0, 0, 1);

	
	glGetFloatv(GL_MODELVIEW_MATRIX, rarm_node.m);
	rarm_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();


	glTranslatef(0, -0.3, 0);
	
	if (a == 0)
	
		glRotatef(45, 0, 0, 1);
		
	
	glRotatef(-angle1, 0, 0, 1);
	

	glGetFloatv(GL_MODELVIEW_MATRIX, ruleg_node.m);
	ruleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.3, 0);

	if(a==1)
	glRotatef(-45, 0, 0, 1);
	
	glRotatef(angle1, 0, 0, 1);
	
	

	glGetFloatv(GL_MODELVIEW_MATRIX, luleg_node.m);
	luleg_node.f = drawLine1;
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	if (a == 1)
	
		glRotatef(45, 0, 0, 1);
	
	glRotatef(-angle1, 0, 0, 1);

	
	
	

	glGetFloatv(GL_MODELVIEW_MATRIX, llleg_node.m);
	llleg_node.f = drawLine1;


	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -0.2, 0);
	if (a == 0)
	
		glRotatef(-45, 0, 0, 1);
	
	glRotatef(angle1, 0, 0, 1);

	
	glGetFloatv(GL_MODELVIEW_MATRIX, rlleg_node.m);
	rlleg_node.f = drawLine1;
	glPopMatrix();
}

//This function will be completed in Assignment 2, you will used drawCircle, drawLine as part of this
void renderStickMan()
{

	traverse(&torso_node);

	
	

	
	

	
	

	

}



//The rountine display() gets called each time the window is redrawn.  Note that this is linked to the command
//glutDisplayFunc(display); which sets this as the display callback


 
void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates - this means that the window will have a coordinate system that goes from -1 to 1 in the x and y direction */
	/* what effect do you think this will have on drawing a square if the window size is not square? */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* clear the screen*/
	glClear(GL_COLOR_BUFFER_BIT);
	
	

	//The glViewport command defines the window that we will be drawing in, here it is the entire screen space
	glViewport(0,0,imageWidth,imageHeight);
	
	

	//In order to draw the image I read in, I am going to draw from the raster position starting at (-1, -1)
	glRasterPos2i(-1,-1);  //Why use -1, -1 ? 
	glDrawPixels(imageWidth,imageHeight,GL_RGB, GL_UNSIGNED_BYTE, image);
	
	//Once I'm done drawing the background image now I want to set up a new drawing area on the screen
	//specifically, I want to draw on top of the index card
	

	if (defaultstick ==1 && stickman==1)
	{
		for (int i = 0; i < count; i++)

		{
			glTranslatef(0, 0.3, 0);
			glTranslatef(sq[i][0], sq[i][1], 0);
			renderStickMan();
			glLoadIdentity();

		}
		
		figure1();


		
	}

	glViewport(103, 71, 245, 190);
	gluOrtho2D(-1, 1, -1, 1);

	if (walkingstick == 1 && a1==0 )
	{
		
			
			renderStickMan();
			

		
		


		figure2();
	}
	glLoadIdentity();
	glViewport(165, 54, 134, 110);
	if (walkingstick == 1 && a1 == 1)
	{

	
		renderStickMan();






		figure2();
	}
	glLoadIdentity();
	glViewport(0, 0, imageWidth, imageHeight);

	if (walkingstick==0 && defaultstick==0)
	{
		for (int i = 0; i < count; i++)

		{
			glTranslatef(0, 0.3, 0);
			glTranslatef(sq[i][0], sq[i][1], 0);
			renderStickMan();
			glLoadIdentity();

		}
	}
		
	
	if (a1==1)
	{

		if (colorvisible == TRUE)
		{



			glScalef(1.05, 1, 1);
			glColor3f(0, 0, 1);

			drawSquare();


		}
	}

		glLoadIdentity();

		if(a1==0)
		{

			if (color1visible == TRUE)
			{


				glColor3f(0, 0, 1);


				drawSquare1();


			}
		}

		

		glLoadIdentity();





	


	
	
	

	

	
	
	
	

	

	/* ready to draw now! forces buffered OGL commands to execute */
	glFlush();
	
}




//If you're using a .png image like I provided you should be fine using this, my images were converted to .png using GIMP


/* Initialize states -- called before */

void init()
{

	figure();

	
	


	



	if (Testvisible == TRUE)
	{
		loadPNG("1.jpg", imageWidth, imageHeight, 24);

		

	}
	if (image1visible == TRUE)
	{
		loadPNG("2.jpg", imageWidth, imageHeight, 24);

		

	}
	unsigned char *flippedImage;
	flippedImage = (unsigned char *)malloc(sizeof (unsigned char)* 3 * 375 * 500);
	flipImag(image, flippedImage);
	image = flippedImage;



	




	image1visible = FALSE;
	Testvisible = FALSE;
	circlevisible = FALSE;
	squarevisible = FALSE;




	/* set background clear color to white */
	glClearColor(1.0, 1.0, 1.0, 0.0);

	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

long timediff(clock_t t1, clock_t t2) {
	
	elapsed = (long)(t2 - t1);
	

	return elapsed;
}


void animation()
{
	//If I want things to move on their own without pressing a button, I need to set up an idle callback function
	//If you look further in the code, you'll see that this function is linked to the glutIdleFunc(animation);
	t2 = clock();
	
	elapsed = timediff(t1, t2);
	
	elapsed2 = timediff(t1, t2);
	//elapsed1 = elapsed + 1000;
	//elapsed1 = elapsed1 % 2000;

	elapsed = elapsed % 2000;
	
	

	angle = ((double)elapsed / 1000) * 30;
	
	
	
	
	if (angle> 30)
	{
		angle = 60 - angle;
	}
	angle1 = ((double)elapsed / 1000) * 45;
	if (angle1 > 45)
	{
		angle1 = 90 - angle1;
	}
	angle2 = ((double)elapsed / 1000) * 180;
	if (angle2 > 180)
	{
		angle2 = 360 - angle2;
	}
	elapsed2 = elapsed2 % 20000;

	translatex = (((double)elapsed2 /10000)*1.6);

	if (translatex >1.6 )
	{	translatex = 3.2 - translatex;
	a = 1;
	}
	if (translatex < 0.01)
	{
		a = 0;
	}


	
	



	 
	//This command then forces the program to go to the display function (or whatever function you linked to glutDisplayFunc)
	//Thus, you use this function to update global variables that can cause animation in the rendering
	glutPostRedisplay();
}


//Here is my menu callback function
void SelectFromMenu(int idCommand)
{
	switch (idCommand)
	{

	case 0:
		colorvisible = TRUE;
		color1visible = TRUE;
		
		
		display();
		break;
	case 1:
		colorvisible = FALSE;
		color1visible = FALSE;

		display();
		break;
	case 2:
		image1visible = TRUE;
		a1 = 1;
		init();
		break;

	case 3:
		Testvisible = TRUE;
		a1 = 0;
		
		init();
		break;
	case 4:
		exit(4);
		break;

	case 5:
		walkingstick = 0;
		defaultstick = 1;

		display();
		break;
	case 6:
		defaultstick = 0;
		walkingstick = 1;
		display();
		break;
	}
  // Almost any menu selection requires a redraw
  glutPostRedisplay();
}

//Here I will initialize the menu, for Assignment 1 you will need to create other menu entries with sub-entries
//Specifically, you'll be creating a menu entry "Images" with sub entries "1" and "2" as well as a menu entry "Draw" with sub entries "square" and "circle"
int BuildPopupMenu (void)
{
	
	int submenu;
	submenu = glutCreateMenu (SelectFromMenu);
	glutAddMenuEntry("on", 0);
	glutAddMenuEntry("off", 1);
	int submenu1;
	submenu1 = glutCreateMenu(SelectFromMenu);
	glutAddMenuEntry("ME", 2);
	glutAddMenuEntry("index card", 3);
	int submenu2;
		submenu2 = glutCreateMenu(SelectFromMenu);
		glutAddMenuEntry("Default", 5);
		glutAddMenuEntry("Walking", 6);


  //This links a callback function "SelectFromMenu", and that link is saved as the integer menu which is then
	int menu;
	menu = glutCreateMenu(SelectFromMenu);                                       //returned to be linked to the right mouse button
  
  glutAddSubMenu("Filled", submenu);
  glutAddSubMenu("Images", submenu1);
  glutAddMenuEntry("Exit demo", 4);
  glutAddSubMenu("Stickman",submenu2);

 
  
	  
  
 

	   //This adds an entry into the menu, if you right click, you'll see "Exit Demo" and this will
                                             //send the value MENU_EXIT to the callback function
 return menu;
}

//ALL STUDENTS: You need to fill out this function for getting the image color
//HINT: Use the test.png image to help you debug
void getImageColor(unsigned char* image, int pixel_x, int pixel_y, unsigned char *RED, unsigned char *GREEN, unsigned char *BLUE)
{
	int z = 3 * (pixel_x + imageWidth * (imageHeight - pixel_y));
	*RED = image[z];
	*GREEN = image[z + 1];
	*BLUE = image[z + 2];
}




//Here is the mouse callback function, you will need to use the x, y coordinate intelligently to get the color of the pixel that is clicked on.
//You must have a printf statement here as well that prints out the coordinate and the color from the background image at the location
void myMouse(int button, int state, int x, int y)
{
	//You need to think about the x and y coordinate that you get here and if they are what you expect
	
	switch (button)
	{
		int f = 0;
	    case GLUT_LEFT_BUTTON:
			
			if (state == GLUT_DOWN)
			{


				getImageColor(image, x, y, &Red, &Green, &Blue);




				printf(" Screen Click R= %u ", Red);

				printf("G=%u ", Green);

				printf("B=%u ", Blue);
				printf("\n");

				X = x;
				Y = y;
				printf("%f", X);
				printf("%f", Y);

				X = (X - (imageWidth/2)) / (imageWidth/2);
				Y = -(Y - (imageHeight/2)) / (imageHeight/2);
				
				
				stickman = 1;
				 stick++;
				int index_size = (stick - 1) % 3;
				sq[index_size][0] = X;
				sq[index_size][1] = Y;

				if (count < 3)
				{
					count++;
				}

				
				
					glutPostRedisplay();
				



				
				
				

				
				//Do something (this is just example if/else statements and not intended to demonstrate anything)
			}
		break;
	}
}


/* The main program */
int main(int argc, char** argv)
{

	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(imageWidth, imageHeight);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Assignment - 1");

	/* create a callback routine for when the mouse is clicked */
	glutMouseFunc(myMouse);

	t1 = clock();
	
	/* create a callback routine for when the program is idle */
	glutIdleFunc(animation);
	
	 
	 
	

	/* create a callback routine for (re-)display */
	glutDisplayFunc(display);

	BuildPopupMenu ();  //This is going to be a function you write to initialize the menu
    glutAttachMenu (GLUT_RIGHT_BUTTON);  //This attaches the menu to the right mouse click  button

	/* init some states */
	init();
	

	/* entering the event loop */
	glutMainLoop();

	/* code here will not be executed */
}
