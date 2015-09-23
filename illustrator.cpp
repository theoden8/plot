#include <GLUT/glut.h>

#include <iostream>
#include <vector>
#include <string>

#include <cstdlib>
#include <cmath>

typedef double real_t;

std::vector <real_t> data;

real_t
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

void DrawText(real_t x, real_t y, const std::string &str) {
	glRasterPos2f(x, y);
	for(size_t i = 0; i < str.length(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
}

inline void DrawPoint(real_t x, real_t y) {
	real_t
		point_x = 2 * x - shift_x,
		point_y = 2 * y - shift_y;
	if(point_x < 0 || point_x >= width ||
		point_y < 0 || point_y >= height)
		return;
	glPushMatrix();	                                        //Push and pop the current matrix stack
	glTranslatef(point_x, point_y, 0);                      //Multiplies the current matrix by a translation matrix
	glBegin(GL_QUADS);                                      //Delimit the verticles of a primitive or a group of like primitives
		glVertex3f(  bold_x,  bold_y, 0.0);             //Specifies a vertex
		glVertex3f(  bold_x, -bold_y, 0.0);             //Specifies a vertex
		glVertex3f( -bold_x, -bold_y, 0.0);             //Specifies a vertex
		glVertex3f( -bold_x,  bold_y, 0.0);             //Specifies a vertex
	glEnd();
	glPopMatrix();
}

void Display() {
	glLoadIdentity();                                       //Replace current matrix with the identity matrix.
	glClear(GL_COLOR_BUFFER_BIT);                           //Clear buffer to preset values.
	glMatrixMode(GL_PROJECTION);                            //Specify which matrix is the current matrix. main::options: GL_MODELVIEW GL_PROJECTION GL_TEXTURE.
	glOrtho(0, width, 0, height, 1, -1);                    //Multiply the current matrix with an orthographic matrix.

	glColor3f(0.8f,0.6f,0.0f);
	DrawText(width - 230 * width/size_x,
		height - 30 * height/size_y,
		("Width:  " + std::to_string(width)));
	DrawText(width - 230 * width/size_x,
		height - 60 * height/size_y,
		("Height: " + std::to_string(height)));

	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		real_t
			*x = &i,
			*y = &data[i];
		DrawPoint(*x, *y);
	}

	glColor3f(1.0f,1.0f,0.0f);
	//Abscissa
	glPushMatrix();
	glTranslatef(0, -shift_y, 0);
	glBegin(GL_QUADS);
		glVertex3f(0,	   bold_y / 2	, 0.0);
		glVertex3f(0,	  -bold_y / 2	, 0.0);
		glVertex3f(width, -bold_y / 2	, 0.0);
		glVertex3f(width,  bold_y / 2	, 0.0);
	glEnd();
	glPopMatrix();

	//Ordinata
	glPushMatrix();
	glTranslatef(-shift_x, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(-bold_x / 2, 0      , 0.0);
		glVertex3f( bold_x / 2, 0      , 0.0);
		glVertex3f( bold_x / 2, height , 0.0);
		glVertex3f(-bold_x / 2, height , 0.0);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int new_size_x, int new_size_y) {
	width *= real_t(new_size_x) / size_x;
	height *= real_t(new_size_y) / size_y;

	size_x = new_size_x;
	size_y = new_size_y;

	bold_x = BOLD * width/size_x;
	bold_y = BOLD * height/size_y;

	glViewport(0, 0, size_x, size_y);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	real_t
		increase = 1 + change,
		decrease = 1 / increase;
	switch(key) {
		case  27:
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'm':
			width   *= decrease;
			height  *= decrease;
			shift_x *= decrease;
			shift_y *= decrease;
			break;
		case 'M':
			width   *= increase;
			height  *= increase;
			shift_x *= increase;
			shift_y *= increase;
			break;
		case 'b':
			BOLD    *= decrease;
			break;
		case 'B':
			BOLD    *= increase;
			break;
		case 't':
			width   *= decrease;
			shift_x *= decrease;
			break;
		case 'T':
			width   *= increase;
			shift_x *= increase;
			break;
		case 'y':
			height  *= decrease;
			shift_y *= decrease;
			break;
		case 'Y':
			height  *= increase;
			shift_y *= increase;
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

void FillData(std::vector <real_t> &data) {
	real_t value;
	while(std::cin >> value)
		data.push_back(value);
}

int main(int argc, char **argv) {
	FillData(data);
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
