#pragma once

#include <stdarg.h>
#include "glut_config.h"

#include "Types.hpp"

struct axis {
	real_t
		winsize,
		gridsize,
		shift,
		thickness;
	real_t
		lborder,
		rborder;
private:
	void reborder() {
		lborder = -gridsize / 2. + shift;
		rborder = gridsize / 2. + shift;
	}
public:
	axis(real_t winsize, real_t thickness, real_t shift = 0.):
		winsize(winsize), gridsize(winsize * 4), thickness(thickness), shift(shift),
		lborder(-gridsize/2. + shift), rborder(gridsize/2. + shift)
	{}

	real_t bold() const {
		return thickness * gridsize / winsize;
	}

	void set_grid(real_t diff) {
		gridsize *= diff;
		reborder();
	}

	void set_shift(real_t diff) {
		shift += gridsize * (diff - 1);
		reborder();
	}

	void set_size(real_t newsize) {
		set_grid(newsize / winsize);
		winsize = newsize;
	}
};


#include <stdio.h>
class Graphics {
	static axis x_, y_;
public:
	const static axis &x() { return x_; }
	const static axis &y() { return y_; }
	static void InitOpenGL(int *argc, char **argv, const char *name);
private:
	static void Display();

	//GraphicsDisplay
	static void DisplayText(real_t x, real_t y, const char *fmt, ...);
	static void DisplayVariables();
	static void DisplayAxis();

	//here
	static inline void DisplayPoint(const real_t &x, const real_t &y) {
		if(
			y < y_.lborder
			|| y > y_.rborder
			|| x < x_.lborder
			|| x > x_.rborder
		)
		{
			return;
		} else {
			real_t xx = x - x_.lborder,
				   yy = y - y_.lborder;
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
