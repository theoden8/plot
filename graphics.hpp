#pragma once

#include "glut_config.h"

#define str(x) std::to_string(x).c_str()
typedef double real_t;

struct axis {
	real_t
		winsize,
		sizeth,
		shift,
		thickness;
public:
	axis(real_t winsize, real_t thickness, real_t shift = 0.):
		winsize(winsize), sizeth(winsize * 4), thickness(thickness), shift(shift)
	{}

	real_t bold() const {
		return thickness * sizeth / winsize;
	}

	real_t set_size(real_t newsize) {
		sizeth *= newsize / winsize;
		winsize = newsize;
	}

	real_t set_shift(real_t change) {
		shift += sizeth * change;
	}
};


axis
	xxx(800, 3),
	yyy(800, 3);


void DrawText(real_t x, real_t y, const char *str) {
	glRasterPos2f(x, y);
	for(const char *c = str; *c; ++c)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}

void ShowVariables() {
	glColor3f(0.0f, 0.7f, 0.7f);
	DrawText(
		xxx.sizeth - 260 * xxx.sizeth/xxx.winsize,
		yyy.sizeth - 30 * yyy.sizeth/yyy.winsize,
		(std::string("WIDTH:  ") + str(xxx.sizeth)).c_str());
	DrawText(
		xxx.sizeth - 260 * xxx.sizeth/xxx.winsize,
		yyy.sizeth - 60 * yyy.sizeth/yyy.winsize,
		(std::string("HEIGHT: ") + str(yyy.sizeth)).c_str());
	glColor3f(1.0f, 1.0f, 0.0f);
	DrawText(
		0.02 * xxx.sizeth,
		0.92 * yyy.sizeth,
		(std::string() + "CENTER: (" + str(xxx.shift) + ", " + str(yyy.shift) + ")").c_str()
	);
}


inline void DrawDot(const real_t &x, const real_t &y) {
	glPushMatrix();	                                        //Push and pop the current matrix stack
	glTranslatef(x, y, 0);                      //Multiplies the current matrix by a translation matrix
	glBegin(GL_QUADS);                                      //Delimit the verticles of a primitive or a group of like primitives
		glVertex3f(  xxx.bold(),  yyy.bold(), 0.0);             //Specifies a vertex
		glVertex3f(  xxx.bold(), -yyy.bold(), 0.0);             //Specifies a vertex
		glVertex3f( -xxx.bold(), -yyy.bold(), 0.0);             //Specifies a vertex
		glVertex3f( -xxx.bold(),  yyy.bold(), 0.0);             //Specifies a vertex
	glEnd();
	glPopMatrix();
}

inline void DrawPoint(const real_t &x, const real_t &y) {
	if(y > yyy.sizeth / 2. + yyy.shift ||
			y < -yyy.sizeth / 2. - yyy.shift)
		return;
	else
		DrawDot(xxx.sizeth / 2. + 2 * x - xxx.shift, yyy.sizeth / 2. + 2 * y - yyy.shift);
}


void DrawAxis() {
	glColor3f(1.0f, 1.0f, 0.0f);
	//Abscissa
	glPushMatrix();
	glTranslatef(0, yyy.sizeth / 2. - yyy.shift, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,  yyy.bold() / 2., 0.0);
		glVertex3f(0, -yyy.bold() / 2., 0.0);
		glVertex3f(xxx.sizeth, -yyy.bold() / 2., 0.0);
		glVertex3f(xxx.sizeth,  yyy.bold() / 2., 0.0);
	glEnd();
	glPopMatrix();

	//Ordinata
	glPushMatrix();
	glTranslatef(xxx.sizeth / 2. - xxx.shift, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(-xxx.bold() / 2., 0., 0.0);
		glVertex3f( xxx.bold() / 2., 0., 0.0);
		glVertex3f( xxx.bold() / 2., yyy.sizeth , 0.0);
		glVertex3f(-xxx.bold() / 2., yyy.sizeth , 0.0);
	glEnd();
	glPopMatrix();
}

void Reshape(int new_size_x, int new_size_y) {
	xxx.set_size(new_size_x);
	yyy.set_size(new_size_y);

	glViewport(0, 0, xxx.winsize, yyy.winsize);
	glutPostRedisplay();
}

void Keyboard(unsigned char key) {
	static const real_t
		change = 0.05;
	static const real_t
		increase = 1 + change,
		decrease = 1 / increase;
	switch(key) {
		case  27:
		case 'q':
		case 'Q':
			exit(0);
		case 'm':
			xxx.sizeth    *= decrease;
			yyy.sizeth    *= decrease;
			xxx.shift     *= decrease;
			yyy.shift     *= decrease;
		break;
		case 'M':
			xxx.sizeth    *= increase;
			yyy.sizeth    *= increase;
			xxx.shift     *= increase;
			yyy.shift     *= increase;
		break;
		case 'b':
			xxx.thickness *= decrease;
			yyy.thickness *= decrease;
		break;
		case 'B':
			xxx.thickness *= increase;
			yyy.thickness *= increase;
		break;
		case 't':
			xxx.sizeth    *= decrease;
			xxx.shift     *= decrease;
		break;
		case 'T':
			xxx.sizeth    *= increase;
			xxx.shift     *= increase;
		break;
		case 'y':
			yyy.sizeth    *= decrease;
			yyy.shift     *= decrease;
		break;
		case 'Y':
			yyy.sizeth    *= increase;
			yyy.shift     *= increase;
		break;
		case 'w':
			yyy.set_shift(+change);
		break;
		case 's':
			yyy.set_shift(-change);
		break;
		case 'a':
			xxx.set_shift(-change);
		break;
		case 'd':
			xxx.set_shift(+change);
		break;
	}
}


void Special(int key) {
	switch(key) {
		case 100 :
			Keyboard('a');
			break;
		case 101 :
			Keyboard('w');
			break;
		case 102 :
			Keyboard('d');
			break;
		case 103 :
			Keyboard('s');
			break;
	}
	glutPostRedisplay();
}
