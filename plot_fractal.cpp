#include <cassert>
#include <vector>
#include <cmath>

#include "Graphics.hpp"

#include "FractalIterDiscrete.hpp"
#include "FractalIterLine.hpp"

#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

#define PLOTFRACTAL KochsFlake

PLOTFRACTAL g_fractal = PLOTFRACTAL();

void Graphics::ExtendedDisplay() {
	G_COLOR(.0, 1., .0);
	g_fractal.Draw();

	G_COLOR(.7, .7, 1.);
	DisplayText(
		0.02 * x_.gridsize, 0.98 * y_.gridsize,
		"Fractal: " TOSTR(PLOTFRACTAL)
	);

	G_COLOR(.0, .7, .7);
	DisplayText(
		0.02 * x_.gridsize, 0.95 * y_.gridsize,
		"level == %d", g_fractal.level()
	);
}

void Graphics::ExtendedKeyboard(unsigned char key, int x, int y) {
	g_fractal.Keyboard(key);
	Keyboard(key);
	Display();
}

int main(int argc, char *argv[]) {
	Graphics::InitOpenGL(&argc, argv, "plot_fractal");
}
