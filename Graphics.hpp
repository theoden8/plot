#pragma once

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

	void set_size(real_t newsize) {
		sizeth *= newsize / winsize;
		winsize = newsize;
	}

	void set_shift(real_t change) {
		shift += sizeth * change;
	}
};


class Graphics {
	static axis x_, y_;
public:
	static void InitOpenGL(int *argc, char **argv, const char *name);
private:
	static void Display();

	//Graphics
	static void DisplayText(real_t x, real_t y, const char *str);
	static void DisplayVariables();
	static void DisplayAxis();

	// separately here
	static inline void DisplayPoint(const real_t &x, const real_t &y) {
		if(y > y_.sizeth / 2. + y_.shift ||
				y < -y_.sizeth / 2. - y_.shift) {
			return;
		} else {
			real_t x = x_.sizeth / 2. + 2 * x - x_.shift,
				   y = y_.sizeth / 2. + 2 * y - y_.shift;
			glPushMatrix();	              //Push and pop the current matrix stack
			glTranslatef(x, y, 0);        //Multiplies the current matrix by a translation matrix
			glBegin(GL_QUADS);            //Delimit the verticles of a primitive or a group of like primitives
				glVertex3f(  x_.bold(),  y_.bold(), 0.0);    //Specifies a vertex
				glVertex3f(  x_.bold(), -y_.bold(), 0.0);    //Specifies a vertex
				glVertex3f( -x_.bold(), -y_.bold(), 0.0);    //Specifies a vertex
				glVertex3f( -x_.bold(),  y_.bold(), 0.0);    //Specifies a vertex
			glEnd();
			glPopMatrix();
		}
	}

	//GraphicsFuncs
	static void Reshape(int new_size_x, int new_size_y);
	static void Keyboard(unsigned char key);
	static void Special(int key, int x, int y);

	//defined within project
	static void ExtendedDisplay();
	static void ExtendedKeyboard(unsigned char key, int x, int y);
};
