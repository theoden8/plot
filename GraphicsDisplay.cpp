#include <stdio.h>
#include "glut_config.h"

#include "Graphics.hpp"


void Graphics::Display() {
	glLoadIdentity();                                 //Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);                     //Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);                      //Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, x_.gridsize, 0, y_.gridsize, 1, -1);   //Multiply the current matrix with an orthographic matrix.

	DisplayVariables();
	DisplayAxis();
	ExtendedDisplay();

	glutSwapBuffers();
}

void Graphics::DisplayText(real_t x, real_t y, const char *fmt, ...) {
	static char str[1 << 6];

	va_list args;
	va_start(args, fmt);
	vsprintf(str, fmt, args);
	va_end(args);

	glRasterPos2f(x, y);
	for(const char *c = str; *c; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void Graphics::DisplayVariables() {
	glColor3f(0.0f, 0.7f, 0.7f);
	DisplayText(
		x_.gridsize - 260 * x_.gridsize / x_.winsize,
		y_.gridsize - 30 * y_.gridsize / y_.winsize,
		"WIDTH: %lf", x_.gridsize
	);
	DisplayText(
		x_.gridsize - 260 * x_.gridsize/x_.winsize,
		y_.gridsize - 60 * y_.gridsize/y_.winsize,
		"HEIGHT: %lf", y_.gridsize
	);
	glColor3f(1.0f, 1.0f, 0.0f);
	DisplayText(
		0.02 * x_.gridsize,
		0.92 * y_.gridsize,
		"CENTER: (%lf, %lf)", x_.shift, y_.shift
	);
}

void Graphics::DisplayAxis() {
	glColor3f(1.0f, 1.0f, 0.0f);
	//Abscissa
	glPushMatrix();
	glTranslatef(0, y_.gridsize / 2. - y_.shift, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,  y_.bold() / 2., 0.0);
		glVertex3f(0, -y_.bold() / 2., 0.0);
		glVertex3f(x_.gridsize, -y_.bold() / 2., 0.0);
		glVertex3f(x_.gridsize,  y_.bold() / 2., 0.0);
	glEnd();
	glPopMatrix();

	//Ordinata
	glPushMatrix();
	glTranslatef(x_.gridsize / 2. - x_.shift, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(-x_.bold() / 2., 0., 0.0);
		glVertex3f( x_.bold() / 2., 0., 0.0);
		glVertex3f( x_.bold() / 2., y_.gridsize , 0.0);
		glVertex3f(-x_.bold() / 2., y_.gridsize , 0.0);
	glEnd();
	glPopMatrix();
}
