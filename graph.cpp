#include <cassert>
#include <vector>
#include <cmath>

#include "Graphics.hpp"

static real_t
	g_step = 0.1;

#define PLOTFUNC(x) exp(x)
#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

void Graphics::ExtendedDisplay() {
	glColor3f(0.7f, 0.7f, 1.0f);
	DisplayText(
		0.02 * x_.gridsize, 0.98 * y_.gridsize,
		"f(x) = " TOSTR(PLOTFUNC(x))
	);

	glColor3f(1.0f, 0.7f, 0.7f);
	DisplayText(
		0.02 * x_.gridsize, 0.95 * y_.gridsize,
		"g_step == %lf", g_step
	);

	if(g_step == 0.)
		return;

	glColor3f(0.0f, 1.0f, 0.0f);
	for(
		real_t x = x_.lborder;
		x <= x_.rborder;
		x += g_step
	)
	{
		/* printf("%lf\t%lf:%lf\n", x, x_.gridsize, x_.shift); */
		DisplayPoint(x, PLOTFUNC(x));
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
			g_step *= increase;
		break;
		case '-':
		case '_':
			g_step *= decrease;
		break;
	}
	Keyboard(key);
	Display();
}

int main(int argc, char **argv) {
	Graphics::InitOpenGL(&argc, argv, "graph");
}
