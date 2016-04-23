#include "glut_config.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

#include "graphics.hpp""

typedef long double real_t;

real_t
	STEP    = 0.1,  BOLD    = 0.5,   change = 0.05,
	width   = 300,  height  = width,
	size_x  = 800,  size_y  = 800,
	shift_x = 0,    shift_y = 0;

const char *function = "f(x) = log(x)";
real_t calc(const real_t &x) {
	real_t y = log(x);
	return y;
}

void Display() {
	if(!STEP)
		throw std::runtime_error("Step equals 0, can not perform the task.");
	glLoadIdentity();				//Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);			//Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);			//Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, width, 0, height, 1, -1);		//Multiply the current matrix with an orthographic matrix.

	glColor3f(0.7f,0.7f,1.0f);
	DrawText(0.02 * width, 0.98 * height, function);

	glColor3f(1.0f,0.7f,0.7f);
	DrawText(0.02 * width, 0.95 * height, std::string("STEP == ", str(STEP)).c_str());

	glColor3f(0.0f,0.7f,0.7f);
	DrawText(0.02 * width, 0.92 * height, std::string("WIDTH == ", str(width)).c_str());
	DrawText(0.02 * width, 0.89 * height, std::string("HEIGHT == ", str(height)).c_str());

	glColor3f(1.0f,1.0f,0.0f);
	DrawText(0.02 * width, 0.86 * height, (std::string("CENTER: (") + str(shift_x) + ", " + str(shift_y) + ")").c_str());

	glColor3f(0.0f,1.0f,0.0f);
	for(real_t x = -width + shift_x; x <= width + shift_x; x += STEP) {
		real_t y = calc(x);
		if(y > height/2 + shift_y
		   || y < -height/2 - shift_y)
		{
			continue;
		}
		DrawDot(x, y, BOLD, BOLD);
	}

	glColor3f(1.0f,1.0f,0.0f);

	//abscissa
	glPushMatrix();
	glTranslatef(0, height/2 - shift_y, 0);
	glBegin(GL_QUADS);
		glVertex3f( 0,	+BOLD/2		, 0.0);
		glVertex3f( 0,	-BOLD/2		, 0.0);
		glVertex3f( width, -BOLD/2	, 0.0);
		glVertex3f( width, +BOLD/2	, 0.0);
	glEnd();
	glPopMatrix();

	//ordinata
	glPushMatrix();
	glTranslatef(width/2 - shift_x, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f( -BOLD/2, 0		, 0.0);
		glVertex3f( +BOLD/2, 0		, 0.0);
		glVertex3f( +BOLD/2, height	, 0.0);
		glVertex3f( -BOLD/2, height	, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int new_size_x, int new_size_y) {
	width *= real_t(new_size_x)/size_x;
	height *= real_t(new_size_y)/size_y;

	size_x = new_size_x;
	size_y = new_size_y;

	glViewport(0, 0, size_x, size_y);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27 :
		case 'q':
		case 'Q':
			exit(0);
			break;
		case '=':
		case '+':
			STEP *= (1 + change);
			STEP *= (1 + change);
			break;
		case '-':
		case '_':
			STEP *= (1 - change);
			STEP *= (1 - change);
			break;
		case 'm':
			width /= (1 + change);
			height /= (1 + change);
			BOLD /= (1 + change);
			break;
		case 'M':
			width *= (1 + change);
			height *= (1 + change);
			BOLD *= (1 + change);
			break;
		case 'b':
			BOLD /= (1 + change);
			break;
		case 'B':
			BOLD *= (1 + change);
			break;
		case 't':
			width *= (1 - change);
			break;
		case 'T':
			width *= (1 + change);
			break;
		case 'y':
			height *= (1 - change);
			break;
		case 'Y':
			height *= (1 + change);
			break;
		case 'w':
			shift_y += height * change;
			break;
		case 's':
			shift_y -= height * change;
			break;
		case 'a':
			shift_x -= width * change;
			break;
		case 'd':
			shift_x += width * change;
			break;
	}
	Display();
}

void Special(int key, int x, int y) {
	switch(key) {
		case 100 :
			Keyboard('a', x, y);
			break;
		case 101 :
			Keyboard('w', x, y);
			break;
		case 102 :
			Keyboard('d', x, y);
			break;
		case 103 :
			Keyboard('s', x, y);
			break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);		//Initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//Set the initial display mode.
	glutInitWindowSize(size_x, size_y);
	glutCreateWindow("grapher");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	Display();

	glutMainLoop();

	return 0;
}
