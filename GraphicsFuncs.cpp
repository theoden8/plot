#include <cstdlib>
#include "glut_config.h"

#include "Graphics.hpp"

axis
	Graphics::x_(800, 3),
	Graphics::y_(800, 3);

void Graphics::InitOpenGL(int *argc, char **argv, const char *name) {
	glutInit(argc, argv);									  //Initialize the GLUT library.
	/* glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);  //Set the initial display mode. */
	glutInitWindowSize(x_.winsize, y_.winsize);
	glutCreateWindow(name);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(ExtendedKeyboard);
	glutSpecialFunc(Special);

	Display();

	glutMainLoop();
}


void Graphics::Reshape(int new_size_x, int new_size_y) {
	x_.set_size(new_size_x);
	y_.set_size(new_size_y);

	glViewport(0, 0, x_.winsize, y_.winsize);
	glutPostRedisplay();
}

void Graphics::Keyboard(unsigned char key) {
	static const real_t
		change = 0.05,
		increase = 1 + change,
		decrease = 1 / increase;
	switch(key) {
		case  27:
		case 'q':
		case 'Q':
			exit(0);
		break;
		case 'm':
			x_.sizeth	*= decrease;
			y_.sizeth	*= decrease;
			x_.shift	*= decrease;
			y_.shift	*= decrease;
		break;
		case 'M':
			x_.sizeth	*= increase;
			y_.sizeth	*= increase;
			x_.shift	*= increase;
			y_.shift	*= increase;
		break;
		case 'b':
			x_.thickness *= decrease;
			y_.thickness *= decrease;
		break;
		case 'B':
			x_.thickness *= increase;
			y_.thickness *= increase;
		break;
		case 't':
			x_.sizeth	*= decrease;
			x_.shift	*= decrease;
		break;
		case 'T':
			x_.sizeth	*= increase;
			x_.shift	*= increase;
		break;
		case 'y':
			y_.sizeth	*= decrease;
			y_.shift	*= decrease;
		break;
		case 'Y':
			y_.sizeth	*= increase;
			y_.shift	*= increase;
		break;
		case 'w':
			y_.set_shift(+change);
		break;
		case 's':
			y_.set_shift(-change);
		break;
		case 'a':
			x_.set_shift(-change);
		break;
		case 'd':
			x_.set_shift(+change);
		break;
	}
}

void Graphics::Special(int key, int x, int y) {
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
	Display();
}
