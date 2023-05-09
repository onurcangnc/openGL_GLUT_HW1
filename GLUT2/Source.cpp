/*********
   CTIS164 - Template Source Program
----------
STUDENT : Onurcan Genç
SECTION : 4
HOMEWORK: Flying UFO shape (Press spacebar to start animating)
----------
PROBLEMS: some drawing issues that are related with trapzeoid which is the body of the
UFO and I tried to move triangles around the sun ,uut we have not learnt it.

----------
ADDITIONAL FEATURES: If you press Numpad: '+' and '-' button you can increase and decrease the
speed of the UFO.
If you press on white circles that are located on the center of the window(pencere kulpu), you can move it right
to left and press the same location if you want to stop and so on.(press the white pencere kulpu that is white color)

if you press 'c' on keyboard clouds immediately start moving and press 'c' to stop them.

if you press also 'space' also sun moves around the border.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1200   
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  50 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false,
space = false, border = false, border2 = false, cloudMove = false;
int  winWidth, winHeight; // current Window width and height

int ufoX = -400, ufoY = 50, speedUfo = 5; // center points of ufo

int cloudX = -300, cloudX2 = +420, cloudX3 = -150, cloudX4 = +250;//clouds Axises

int borderX = -30, borderX2 = 30; // window borders

int sunX = +250, sunY = -150, sunX2 = +250, sunY2 = -150, sunX3 = +250, sunY3 = -150, SpeedSun = 3, SunRadius = 30; // sun coordinates


//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}


void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char* string, void* font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}


//
// To display onto window using OpenGL commands
void window()
{

	glColor3ub(45, 89, 112);
	glRectf(-600, -400, 600, 400);

	glColor3ub(157, 109, 60);
	glRectf(-505, -400, -478, 400);

	glColor3ub(157, 109, 60);
	glRectf(478, -400, 505, 400);

	glColor3ub(255, 255, 255);
	glRectf(505, -305, -505, 305);
	glColor3ub(102, 51, 0);
	glRectf(500, -300, -500, +300);

	glColor3ub(255, 255, 255);
	glRectf(480, -280, -480, 280);


	//Sky
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(475, -275);
	glVertex2i(-475, -275);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(-475, 275);
	glVertex2i(475, 275);
	glEnd();

	glColor3ub(157, 109, 60);
	glRectf(150, +320, -150, +380);
	glColor3f(1, 1, 1);
	vprint(-60, 350, GLUT_BITMAP_8_BY_13, "**Onurcan Genc**");
	vprint(-35, 330, GLUT_BITMAP_8_BY_13, "<22003467>");

	

}





void borders(int borderX, int borderX2) {

	glColor3ub(255, 255, 255);
	glRectf(borderX2 + 5, -275, 5, 275);

	glColor3ub(102, 51, 0);
	glRectf(borderX2, -275, 0, 275);



	glColor3ub(255, 255, 255);
	glRectf(borderX - 5, -275, 5, 275);

	glColor3ub(102, 51, 0);
	glRectf(borderX, -275, 0, 275);


	glColor3ub(255, 255, 255);
	circle(borderX2 - 10, 0, 5);

	glColor3ub(255, 255, 255);
	circle(borderX + 15, 0, 5);


}



void drawUFO(int ufoX, int ufoY)
{

	glColor3ub(0, 255, 0);
	circle(ufoX + 52, ufoY + 16, 10);

	glColor3ub(0, 0, 0);
	glRectf(ufoX + 60, ufoY - 60, ufoX + 45, ufoY + 10);

	glColor3ub(85, 112, 118);
	circle(ufoX + 51, ufoY - 103, 15);

	glColor3ub(133, 189, 162);
	circle(ufoX + 50, ufoY - 50, 50);
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(ufoX, ufoY - 50);
	glVertex2f(ufoX - 20, ufoY - 102);
	glVertex2f(ufoX + 120, ufoY - 102);
	glVertex2f(ufoX + 100, 0);
	glEnd();

	glBegin(GL_LINES);

	glColor3ub(0, 0, 0);
	glLineWidth(4.0f);
	glVertex2f(ufoX + 20, ufoY - 100);
	glVertex2f(ufoX + 10, ufoY - 130);
	glVertex2f(ufoX + 80, ufoY - 100);
	glVertex2f(ufoX + 90, ufoY - 130);
	glEnd();

	glColor3ub(255, 0, 0);
	circle(ufoX + 10, ufoY - 130, 5);
	circle(ufoX + 90, ufoY - 130, 5);

	glLineWidth(4.0f);
	glColor3ub(0, 0, 0);
	circle_wire(ufoX + 50, ufoY - 50, 50);

	glColor3ub(159, 238, 152);
	circle(ufoX + 5, ufoY - 70, 5);
	circle(ufoX + 20, ufoY - 70, 5);

	glColor3ub(85, 112, 118);
	circle(ufoX + 80, ufoY - 70, 5);
	circle(ufoX + 95, ufoY - 70, 5);

	glRectf(ufoX + 42, ufoY - 105, ufoX + 62, ufoY - 50);
	
	

}

void triangle(int x, int y, int x2, int y2, int x3, int y3) {


	glBegin(GL_TRIANGLES);
	glColor3ub(209, 64, 9); // orange
	glVertex2f(x, y);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();


}


void sun(int sunX, int sunY, int SunRadius) {

	glColor3ub(209, 64, 9);
	circle(sunX, sunY, SunRadius);
	glColor3ub(252, 150, 1);
	circle(sunX, sunY, SunRadius - 5);
	glColor3ub(255, 204, 51);
	circle(sunX, sunY, SunRadius - 10);
	glColor3ub(255, 228, 132);
	circle(sunX, sunY, SunRadius - 15);
	glColor3ub(255, 255, 255);
	circle(sunX, sunY, SunRadius - 20);

	triangle(sunX, sunY + 75, sunX2 - 10, sunY2 + 35, sunX3 + 10, sunY3 + 35);
	triangle(sunX - 75, sunY, sunX2 - 35, sunY2 + 10, sunX3 - 35, sunY3 - 10);
	triangle(sunX, sunY - 75, sunX2 - 10, sunY2 - 35, sunX3 + 10, sunY3 - 35);
	triangle(sunX + 75, sunY, sunX2 + 35, sunY2 + 10, sunX3 + 35, sunY3 - 10);
}


void sky() {

	//Sky
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(475, -275);
	glVertex2i(-475, -275);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(-475, 275);
	glVertex2i(475, 275);
	glEnd();
}


void cloud(int cloudX, int cloudX2, int cloudX3, int cloudX4)
{
	glColor3ub(250, 242, 239);
	circle(cloudX - 40, 190, 20);
	circle(cloudX - 70, 190, 20);
	circle(cloudX - 10, 190, 20);
	circle(cloudX - 55, 210, 20);
	circle(cloudX - 25, 210, 20);

	glColor3ub(250, 242, 239);
	circle(cloudX2 - 40, 190, 20);
	circle(cloudX2 - 70, 190, 20);
	circle(cloudX2 - 10, 190, 20);
	circle(cloudX2 - 55, 210, 20);
	circle(cloudX2 - 25, 210, 20);

	glColor3ub(250, 242, 239);
	circle(cloudX3 - 40, 190, 20);
	circle(cloudX3 - 70, 190, 20);
	circle(cloudX3 - 10, 190, 20);
	circle(cloudX3 - 55, 210, 20);
	circle(cloudX3 - 25, 210, 20);

	glColor3ub(250, 242, 239);
	circle(cloudX4 - 40, 190, 20);
	circle(cloudX4 - 70, 190, 20);
	circle(cloudX4 - 10, 190, 20);
	circle(cloudX4 - 55, 210, 20);
	circle(cloudX4 - 25, 210, 20);

}






void display() {
	//
	// clear window to black
	//
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	
	window();
	sky();
	borders(borderX, borderX2);
	sun(sunX, sunY, SunRadius);
	drawUFO(ufoX, ufoY);
	cloud(cloudX, cloudX2, cloudX3, cloudX4);
	borders(borderX, borderX2);
	


	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.



	if (key == '+')
		 speedUfo += 3;

	if (key == '-')
		 speedUfo -= 3;


	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	if (key == ' ')
		space = !space;
	

	if (key == 'c')
		cloudMove = !cloudMove;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	case GLUT_KEY_LEFT:
		left = true;
		break;
	case GLUT_KEY_RIGHT:
		right = true;
		break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case GLUT_KEY_LEFT:
		left = false;
		break;
	case GLUT_KEY_RIGHT:
		right = false;
		break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.

	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {


		if (x >= 567 && x <= 601 && y >= 124 && y <= 670)
			border = !border;
		
		if (x >= 605 && x <= 630 && y >= 124 && y <= 672)
			border2 = !border2;

	}


	// to refresh the window it calls display() function
	glutPostRedisplay();
}



//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (space == true)
		ufoX += speedUfo;

	if (ufoX < -455 || ufoX > 355)
		ufoX = -410;

	if (borderX < -475)
		border = false;

	if (border == true)
		borderX -= 3;

	if (borderX > -475)
		border == false;

	if (borderX < -30 && border == false)
		borderX += 3;

	if (borderX2 > 480)
		border2 = false;
	
	if (border2 == true)
		borderX2 += 3;

	if (borderX2 > 480)
		border2 = false;
	
	if (borderX2 > 30 && border2 == false)
		borderX2 -= 3;
	
	if (space == true && sunY < 160)
	{
		sunY += SpeedSun;
		sunY2 += SpeedSun;
		sunY3 += SpeedSun;
	}

	if (cloudMove == true && sunX > -250) {

		sunX -= SpeedSun;
		sunX2 -= SpeedSun;
		sunX3 -= SpeedSun;

	}
		
	
	

	if (cloudMove == true) {
		cloudX += 3;
		cloudX2 += 3;
		cloudX3 += 3;
		cloudX4 += 3;
	}
		
	if (cloudX4 > 420)
		cloudX4 = -400;
	

	if (cloudX3 > 420)
		cloudX3 = -400;
	
	if (cloudX2 > 420)
		cloudX2 = -400;

	if (cloudX > 420)
		cloudX = -400;

	

	

	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("UFO Graphics Corp.");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}