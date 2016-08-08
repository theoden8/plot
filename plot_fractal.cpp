#include <cassert>
#include <vector>
#include <cmath>

#include "Graphics.hpp"

#include "Functions.hpp"
#include "FractalIterDiscrete.hpp"
#include "FractalIterLine.hpp"

#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

#define PLOTFRACTAL JuliaSet

PLOTFRACTAL g_fractal = PLOTFRACTAL();

GFUNC_DISPLAY {
	RGB_COLOR(.0, 1., .0);
	g_fractal.Draw();

	RGB_COLOR(.7, .7, 1.);
	DisplayText(
		0.02 * x_.gridsize, 0.98 * y_.gridsize,
		"Fractal: " TOSTR(PLOTFRACTAL)
	);

	RGB_COLOR(.0, .7, .7);
	DisplayText(
		0.02 * x_.gridsize, 0.95 * y_.gridsize,
		"level == %d", g_fractal.level()
	);
}

GFUNC_KEYBOARD {
	g_fractal.Keyboard(key);
}

GMAIN {
	GFUNC_INIT("plot_fractal");
}
