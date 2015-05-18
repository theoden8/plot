#include <GLUT/glut.h>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

typedef long double val_t;
typedef std::vector <val_t> intvector_t;
typedef float float_t;
intvector_t DATA;

float_t
	size_x = 800,
	size_y = 800,

	width(size_x * 4),
	height(size_y * 4),

	change = 0.05,

	BOLD = 3,
	bold_x(BOLD * width / size_x),
	bold_y(BOLD * height / size_y),

	shift_x = 0,
	shift_y = 0;

void Type(float_t x, float_t y, const char *string) {
	glRasterPos2f(x, y);
	for (const char *c = string; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}

inline void ArrangeDot(long double x, long double y) {
	if(
		abs(2 * x - shift_x) >= width ||
		abs(2 * y - shift_y) >= height
	)
		return;
	glPushMatrix();		//Push and pop the current matrix stack
	glTranslatef(2 * x - shift_x, 2 * y - shift_y, 0);	//Multiplies the current matrix by a translation matrix
	glBegin(GL_QUADS);	//Delimit the verticles of a primitive or a group of like primitives
		glVertex3f( +bold_x, +bold_y, 0.0);	//Specifies a vertex
		glVertex3f( +bold_x, -bold_y, 0.0);	//Specifies a vertex
		glVertex3f( -bold_x, -bold_y, 0.0);	//Specifies a vertex
		glVertex3f( -bold_x, +bold_y, 0.0);	//Specifies a vertex
	glEnd();
	glPopMatrix();
}

void Display() {
	glLoadIdentity();				//Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);			//Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);			//Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, width, 0, height, 1, -1);		//Multiply the current matrix with an orthographic matrix.

	glColor3f(0.8f,0.6f,0.0f);
	Type(width - 230 * width/size_x, height - 30 * height/size_y, std::string(std::string() + "Width:  " + std::to_string(width)).c_str());
	Type(width - 230 * width/size_x, height - 60 * height/size_y, std::string(std::string() + "Height: " + std::to_string(height)).c_str());

	glColor3f(0.0f,1.0f,0.0f);
	for(val_t i = 0; i < DATA.size(); ++i) {
		val_t *x = &i;
		val_t *y = &DATA[i];
		ArrangeDot(*x, *y);
	}

	glColor3f(1.0f,1.0f,0.0f);
	//abscissa
	glPushMatrix();
	glTranslatef(0, -shift_y, 0);
	glBegin(GL_QUADS);
		glVertex3f( 0,	   +bold_y/2	, 0.0);
		glVertex3f( 0,	   -bold_y/2	, 0.0);
		glVertex3f( width, -bold_y/2	, 0.0);
		glVertex3f( width, +bold_y/2	, 0.0);
	glEnd();
	glPopMatrix();

	//ordinata
	glPushMatrix();
	glTranslatef(- shift_x, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f( -bold_x/2, 0		, 0.0);
		glVertex3f( +bold_x/2, 0		, 0.0);
		glVertex3f( +bold_x/2, height	, 0.0);
		glVertex3f( -bold_x/2, height	, 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int new_size_x, int new_size_y) {
	width *= float_t(new_size_x)/size_x;
	height *= float_t(new_size_y)/size_y;

	size_x = new_size_x;
	size_y = new_size_y;

	bold_x = BOLD * width/size_x;
	bold_y = BOLD * height/size_y;

	glViewport(0, 0, size_x, size_y);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 27 :
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'm':
			width /= (1 + change);
			height /= (1 + change);
			break;
		case 'M':
			width *= (1 + change);
			height *= (1 + change);
			break;
		case 'b':
			BOLD /= (1 + change);
			break;
		case 'B':
			BOLD *= (1 + change);
			break;
		case 't':
			width *= (1 - change);
			break;
		case 'T':
			width *= (1 + change);
			break;
		case 'y':
			height *= (1 - change);
			break;
		case 'Y':
			height *= (1 + change);
			break;
		case 'w':
			shift_y += height * change;
			break;
		case 's':
			shift_y -= height * change;
			break;
		case 'a':
			shift_x -= width * change;
			break;
		case 'd':
			shift_x += width * change;
			break;
	}
	bold_x = BOLD * width/size_x;
	bold_y = BOLD * height/size_y;
	Display();
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
	val_t number, value;
	while(std::cin >> value) {
		DATA.push_back(value);
	}
	glutInit(&argc, argv);		//Initialize the GLUT library.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	//Set the initial display mode.
	glutInitWindowSize(size_x, size_y);
	glutCreateWindow("gl_world");

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
