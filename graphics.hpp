#pragma once

#include "glut_config.h"

template <typename real_t>
void DrawText(real_t x, real_t y, const char *str) {
	glRasterPos2f(x, y);
	for(const char *c = str; *c; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

template <typename real_t>
inline void DrawDot(
	const real_t &x,
	const real_t &y,
	const real_t &bold_x,
	const real_t &bold_y)
{
	glPushMatrix();	                                        //Push and pop the current matrix stack
	glTranslatef(x, y, 0);                      //Multiplies the current matrix by a translation matrix
	glBegin(GL_QUADS);                                      //Delimit the verticles of a primitive or a group of like primitives
		glVertex3f(  bold_x,  bold_y, 0.0);             //Specifies a vertex
		glVertex3f(  bold_x, -bold_y, 0.0);             //Specifies a vertex
		glVertex3f( -bold_x, -bold_y, 0.0);             //Specifies a vertex
		glVertex3f( -bold_x,  bold_y, 0.0);             //Specifies a vertex
	glEnd();
	glPopMatrix();
}

#define str(x) std::to_string(x).c_str()
