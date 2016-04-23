#include "glut_config.h"

#include <cstdlib>
#include <cmath>

#include <iostream>
#include <vector>
#include <string>

#include "graphics.hpp""

typedef double real_t;

std::vector <real_t> data;

struct axis {
	real_t
		winsize,
		sizeth,
		shift,
		thickness;

public:
	axis(real_t winsize, real_t thickness, real_t shift):
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
	x_axis(800, 3, 0),
	y_axis(800, 3, 0);

inline void DrawPoint(real_t x, real_t y) {
	x = 2 * x - x_axis.shift;
	y = 2 * y - y_axis.shift;
	if(
		x < 0 || x >= x_axis.sizeth ||
		y < 0 || y >= y_axis.sizeth
	)
	{
		return;
	}
	DrawDot(x, y, x_axis.bold(), y_axis.bold());
}

void Display() {
	glLoadIdentity();                                       //Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);                           //Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);                            //Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, x_axis.sizeth, 0, y_axis.sizeth, 1, -1);                    //Multiply the current matrix with an orthographic matrix.

	glColor3f(0.8f,0.6f,0.0f);

	DrawText(x_axis.sizeth - 230 * x_axis.sizeth/x_axis.winsize,
		y_axis.sizeth - 30 * y_axis.sizeth/y_axis.winsize,
		(std::string("WIDTH:  ") + str(x_axis.sizeth)).c_str());
	DrawText(x_axis.sizeth - 230 * x_axis.sizeth/x_axis.winsize,
		y_axis.sizeth - 60 * y_axis.sizeth/y_axis.winsize,
		(std::string("HEIGHT: ") + str(y_axis.sizeth)).c_str());

	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		DrawPoint(i, data[i]);
	}

	glColor3f(1.0f,1.0f,0.0f);
	//Abscissa
	glPushMatrix();
	glTranslatef(0, -y_axis.shift, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,  y_axis.bold() / 2, 0.0);
		glVertex3f(0, -y_axis.bold() / 2, 0.0);
		glVertex3f(x_axis.sizeth, -y_axis.bold() / 2, 0.0);
		glVertex3f(x_axis.sizeth,  y_axis.bold() / 2, 0.0);
	glEnd();
	glPopMatrix();

	//Ordinata
	glPushMatrix();
	glTranslatef(-x_axis.shift, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(-x_axis.bold() / 2, 0      , 0.0);
		glVertex3f( x_axis.bold() / 2, 0      , 0.0);
		glVertex3f( x_axis.bold() / 2, y_axis.sizeth , 0.0);
		glVertex3f(-x_axis.bold() / 2, y_axis.sizeth , 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int new_size_x, int new_size_y) {
	x_axis.set_size(new_size_x);
	y_axis.set_size(new_size_y);

	glViewport(0, 0, x_axis.winsize, y_axis.winsize);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
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
			x_axis.sizeth    *= decrease;
			y_axis.sizeth    *= decrease;
			x_axis.shift     *= decrease;
			y_axis.shift     *= decrease;
		break;
		case 'M':
			x_axis.sizeth    *= increase;
			y_axis.sizeth    *= increase;
			x_axis.shift     *= increase;
			y_axis.shift     *= increase;
		break;
		case 'b':
			x_axis.thickness *= decrease;
			y_axis.thickness *= decrease;
		break;
		case 'B':
			x_axis.thickness *= increase;
			y_axis.thickness *= increase;
		break;
		case 't':
			x_axis.sizeth    *= decrease;
			x_axis.shift     *= decrease;
		break;
		case 'T':
			x_axis.sizeth    *= increase;
			x_axis.shift     *= increase;
		break;
		case 'y':
			y_axis.sizeth    *= decrease;
			y_axis.shift     *= decrease;
		break;
		case 'Y':
			y_axis.sizeth    *= increase;
			y_axis.shift     *= increase;
		break;
		case 'w':
			y_axis.set_shift(+change);
		break;
		case 's':
			y_axis.set_shift(-change);
		break;
		case 'a':
			x_axis.set_shift(-change);
		break;
		case 'd':
			x_axis.set_shift(+change);
		break;
	}
	Display();
}

void FillData(std::vector <real_t> &data) {
	real_t value;
	while(std::cin >> value)
		data.push_back(value);
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
	FillData(data);
	glutInit(&argc, argv);                                      //Initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //Set the initial display mode.
	glutInitWindowSize(x_axis.winsize, y_axis.winsize);
	glutCreateWindow("illustrator");

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
