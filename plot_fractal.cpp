#include <cassert>
#include <vector>
#include <cmath>

#include "Graphics.hpp"
#include "Fractal.hpp"

#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

#define PLOTFRACTAL MandelbrotSet

PLOTFRACTAL g_fractal;

void Graphics::ExtendedDisplay() {
	glColor3f(0.7f, 0.7f, 1.0f);
	DisplayText(
		0.02 * x_.gridsize, 0.98 * y_.gridsize,
		"Fractal: " TOSTR(PLOTFRACTAL)
	);

	glColor3f(0.0f, 1.7f, 0.7f);
	DisplayText(
		0.02 * x_.gridsize, 0.95 * y_.gridsize,
		"level == %d", g_fractal.level()
	);

	glColor3f(0.0f, 1.0f, 0.0f);
	static const auto per_point = [](complex_t z, float r, float g, float b) {
		glColor3f(r, g, b);
		DisplayPoint(z.real(), z.imag());
	};
	g_fractal.Draw(per_point);
}

void Graphics::ExtendedKeyboard(unsigned char key, int x, int y) {
	static const real_t
		change = 0.05,
		increase = 1 + change,
		decrease = 1 / increase;
	switch(key) {
		case '0':
			if(g_fractal.level())
				g_fractal.decr();
		break;
		case '9':
			g_fractal.incr();
		break;
	}
	g_fractal.Keyboard(key);
	Keyboard(key);
	Display();
}

int main(int argc, char *argv[]) {
	g_fractal = PLOTFRACTAL();
	Graphics::InitOpenGL(&argc, argv, "plot_fractal");
}
