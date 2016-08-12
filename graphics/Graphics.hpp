#pragma once

#include <stdarg.h>
#include "include/glut_config.h"

#include "Types.hpp"
#include "Axis.hpp"

#include <stdio.h>
class Graphics {
	static axis x_, y_;
public:
	const static axis &x() { return x_; }
	const static axis &y() { return y_; }
	#define GMAIN int main(int argc, char *argv[])
	#define GFUNC_INIT(NAME) Graphics::InitGLUT(&argc, argv, NAME)
	static void InitGLUT(int *argc, char **argv, const char *name);
private:
	static void Display();

	//GraphicsDisplay
	static void DisplayText(real_t x, real_t y, const char *fmt, ...);
	static void DisplayVariables();
	static void DisplayAxis();

public:
	#define RGB_COLOR(R, G, B) glColor3f(R, G, B)
	static inline void DisplayPoint(const complex_t &z) {
		DisplayPoint(z.real(), z.imag());
	}
	static inline void DisplayPoint(const real_t &x, const real_t &y) {
		/* static real_t prev_x = x, prev_y = y; */
		if(
			!x_.in_grid(x)
			|| !y_.in_grid(y)
			/* || std::abs(x - prev_x) <= x_.bold() */
			/* || std::abs(y - prev_y) <= y_.bold() */
		)
		{
			return;
		} else {
			/* prev_x = x; */
			/* prev_y = y; */
			real_t xx = x - x_.lborder,
				   yy = y - y_.lborder;
			glPushMatrix();                                  //Push the current matrix stack
			glTranslatef(xx, yy, 0);                         //Multiplies the current matrix by a translation matrix
			glPointSize((x_.thickness + y_.thickness) / sqrt(2));
			glBegin(GL_POINTS);                               //Delimit the verticles of a primitive or a group of like primitives
				glVertex3f(0., 0., 0.);
			glEnd();
			glPopMatrix();                                   //Pop the current matrix stack
		}
	}

	static inline void DisplayLine(const complex_t &start, const complex_t &fin) {
		if(!(
				x_.in_grid(start.real())
				&& x_.in_grid(fin.real())
				&& y_.in_grid(start.imag())
				&& y_.in_grid(fin.imag())))
		{
			return;
		}
		glPushMatrix();
		glLineWidth((x_.thickness + y_.thickness) / sqrt(2));
		glBegin(GL_LINES);
			glVertex3f(start.real() - x_.lborder, start.imag() - y_.lborder, 0.);
			glVertex3f(fin.real() - x_.lborder, fin.imag() - y_.lborder, 0.);
		glEnd();
		glPopMatrix();
	}
private:
	//GraphicsFuncs
	static void Reshape(int new_size_x, int new_size_y);
	static void GeneralKeyboard(unsigned char key, int x, int y);
	static void Keyboard(unsigned char key);
	static void Special(int key, int x, int y);

	//defined within a project
	#define GFUNC_DISPLAY void Graphics::ExtendedDisplay()
	#define GFUNC_KEYBOARD void Graphics::ExtendedKeyboard(unsigned char key)
	static void ExtendedDisplay();
	static void ExtendedKeyboard(unsigned char key);
};
