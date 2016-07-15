#include "glut_config.h"

#include <cassert>
#include <vector>
#include <string>
#include <cmath>

#include "Graphics.hpp"

real_t
	STEP = 0.1;

const char *function = "f(x) = log(x)";
real_t calc(const real_t &x) {
	real_t y = log(x);
	return y;
}

void Graphics::ExtendedDisplay() {
	glColor3f(0.7f, 0.7f, 1.0f);
	DisplayText(0.02 * x_.sizeth, 0.98 * y_.sizeth, function);

	glColor3f(1.0f, 0.7f, 0.7f);
	DisplayText(0.02 * x_.sizeth, 0.95 * y_.sizeth, (std::string() + "STEP == " + str(STEP)).c_str());

	glColor3f(0.0f, 1.0f, 0.0f);

	assert(STEP != .0);
	for(
		real_t x = -x_.sizeth/2. - x_.shift;
		x <= x_.sizeth/2. + x_.shift;
		x += STEP
	)
	{
		DisplayPoint(x, calc(x));
	}
}

void Graphics::ExtendedKeyboard(unsigned char key, int x, int y) {
	static const real_t
		change = 0.05,
		increase = 1 + change,
		decrease = 1 / increase;
	switch(key) {
		case '=':
		case '+':
			STEP *= increase;
		break;
		case '-':
		case '_':
			STEP *= decrease;
		break;
	}
	Keyboard(key);
	Display();
}

int main(int argc, char **argv) {
	Graphics::InitOpenGL(&argc, argv, "graph");
}
