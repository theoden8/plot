#include "glut_config.h"

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

#include "graphics.hpp""

real_t
	STEP = 0.1;

const char *function = "f(x) = log(x)";
real_t calc(const real_t &x) {
	real_t y = log(x);
	return y;
}

void Display() {
	if(STEP == .0) {
		throw std::runtime_error("Step equals 0, can not perform the task.");
	}
	glLoadIdentity();                      //Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);          //Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);           //Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, xxx.sizeth, 0, yyy.sizeth, 1, -1);   //Multiply the current matrix with an orthographic matrix.

	glColor3f(0.7f, 0.7f, 1.0f);
	DrawText(0.02 * xxx.sizeth, 0.98 * yyy.sizeth, function);

	glColor3f(1.0f, 0.7f, 0.7f);
	DrawText(0.02 * xxx.sizeth, 0.95 * yyy.sizeth, (std::string() + "STEP == " + str(STEP)).c_str());

	ShowVariables();

	glColor3f(0.0f, 1.0f, 0.0f);
	for(real_t x = -xxx.sizeth/2. - xxx.shift; x <= xxx.sizeth/2. + xxx.shift; x += STEP) {
		real_t y = calc(x);
		DrawPoint(x, y);
	}

	DrawAxis();

	glutSwapBuffers();
}

void ExtendedKeyboard(unsigned char key, int x, int y) {
	static const real_t
		change = 0.05;
	switch(key) {
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
	}
	Keyboard(key);
	Display();
}

void ExtendedSpecial(int key, int x, int y) {
	Special(key);
	Display();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);		//Initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//Set the initial display mode.
	glutInitWindowSize(xxx.winsize, yyy.winsize);
	glutCreateWindow("graph");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(ExtendedKeyboard);
	glutSpecialFunc(ExtendedSpecial);

	Display();
	glutMainLoop();

	return 0;
}
