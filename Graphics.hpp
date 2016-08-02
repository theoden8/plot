#pragma once

#include <stdarg.h>
#include <complex>
#include "glut_config.h"

typedef double real_t;
typedef std::complex <real_t> complex_t;

struct axis {
	real_t
		winsize,
		gridsize,
		shift,
		thickness;
public:
	axis(real_t winsize, real_t thickness, real_t shift = 0.):
		winsize(winsize), gridsize(winsize * 4), thickness(thickness), shift(shift)
	{}

	real_t bold() const {
		return thickness * gridsize / winsize;
	}

	void set_size(real_t newsize) {
		gridsize *= newsize / winsize;
		winsize = newsize;
	}

	void set_shift(real_t change) {
		shift += gridsize * change;
	}
};


#include <stdio.h>
class Graphics {
	static axis x_, y_;
public:
	static void InitOpenGL(int *argc, char **argv, const char *name);
private:
	static void Display();

	//GraphicsDisplay
	static void DisplayText(real_t x, real_t y, const char *fmt, ...);
	static void DisplayVariables();
	static void DisplayAxis();

	//here
	static inline void DisplayPoint(const real_t &x, const real_t &y) {
		if(y < -y_.gridsize / 2. + y_.shift ||
				y > y_.gridsize / 2. + y_.shift) {
			return;
		} else {
			real_t xx = x_.gridsize / 2. + x - x_.shift,
				   yy = y_.gridsize / 2. + y - y_.shift;
			glPushMatrix();                                  //Push the current matrix stack
			glTranslatef(xx, yy, 0);                           //Multiplies the current matrix by a translation matrix
			glBegin(GL_QUADS);                               //Delimit the verticles of a primitive or a group of like primitives
			glVertex3f(  x_.bold(),  y_.bold(), 0.0);        //Specifies a vertex for GL_QUAD
			glVertex3f(  x_.bold(), -y_.bold(), 0.0);
			glVertex3f( -x_.bold(), -y_.bold(), 0.0);
			glVertex3f( -x_.bold(),  y_.bold(), 0.0);
			glEnd();
			glPopMatrix();                                   //Pop the current matrix stack
		}
	}

	//GraphicsFuncs
	static void Reshape(int new_size_x, int new_size_y);
	static void Keyboard(unsigned char key);
	static void Special(int key, int x, int y);

	//defined within a project
	static void ExtendedDisplay();
	static void ExtendedKeyboard(unsigned char key, int x, int y);
};
