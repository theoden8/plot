#include <cassert>
#include <vector>
#include <cmath>

#include "Graphics.hpp"

static complex_t
	g_step(1., 1.);

#define PLOTFUNC(z) exp(z)
#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

void Graphics::ExtendedDisplay() {
	glColor3f(0.7f, 0.7f, 1.0f);
	DisplayText(
		0.02 * x_.gridsize, 0.98 * y_.gridsize,
		"f(z) = " TOSTR(PLOTFUNC(z))
	);

	glColor3f(1.0f, 0.7f, 0.7f);
	DisplayText(
		0.02 * x_.gridsize, 0.95 * y_.gridsize,
		"g_step == (%lf, %lf)", g_step.real(), g_step.imag()
	);

	if(std::abs(g_step - complex_t(0., 0.)) < .0000001)
		return;

	glColor3f(0.0f, 1.0f, 0.0f);
	for(
		real_t x = x_.lborder;
		x <= x_.rborder;
		x += g_step.real()
	)
	{
		for(
			real_t y = y_.lborder;
			y <= y_.rborder;
			y += g_step.imag()
		)
		{
			/* printf("%lf %lf\n", x, y); */
			complex_t z(x, y);
			z = PLOTFUNC(z);
			DisplayPoint(z.real(), z.imag());
		}
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
			g_step *= complex_t(increase, 0);
		break;
		case '-':
		case '_':
			g_step *= complex_t(decrease, 0);
		break;
	}
	Keyboard(key);
	Display();
}

int main(int argc, char **argv) {
	Graphics::InitOpenGL(&argc, argv, "graph_i");
}
