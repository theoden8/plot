#include "glut_config.h"

#include <cstdlib>
#include <cmath>

#include <iostream>
#include <vector>
#include <string>

#include "graphics.hpp""

std::vector <real_t> data;

void Display() {
	glLoadIdentity();                                       //Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);                           //Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);                            //Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, xxx.sizeth, 0, yyy.sizeth, 1, -1);     //Multiply the current matrix with an orthographic matrix.

	ShowVariables();

	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		DrawPoint(i, data[i]);
	}

	DrawAxis();

	glutSwapBuffers();
}

void ExtendedKeyboard(unsigned char key, int x, int y) {
	Keyboard(key);
	Display();
}

void ExtendedSpecial(int key, int x, int y) {
	Special(key);
	Display();
}


void FillData(std::vector <real_t> &data) {
	real_t value;
	while(std::cin >> value)
		data.push_back(value);
}

int main(int argc, char **argv) {
	FillData(data);
	glutInit(&argc, argv);                                      //Initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //Set the initial display mode.
	glutInitWindowSize(xxx.winsize, yyy.winsize);
	glutCreateWindow("illustrator");

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
