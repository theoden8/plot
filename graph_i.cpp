#include <cassert>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "Functions.hpp"
#include "Graphics.hpp"

static complex_t
	g_step(10., 10.);

#define PLOTFUNC(z) (sinh(cos(z)))
#define STRFY(x) #x
#define TOSTR(x) STRFY(x)

GFUNC_DISPLAY {
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

	/*
	 * The plot is limited to only two dimensions (actually, three) and is used
	 * for showing F(Z).
	 * Therefore colors will add enough (3) dimensions to show Z.
	 * The following gives the three color centers such that:
	 *	col(z) = ( abs(red - z), abs(green - z), abs(blue - z) )
	 */
	const complex_t
		lborder(x_.lborder, y_.lborder),
		rborder(x_.rborder, y_.lborder),

		center_red(.0, .0),
		center_green(x_.gridsize, y_.gridsize / 3.),
		center_blue(x_.gridsize / 3., y_.gridsize);

	for(
		real_t x = x_.lborder;
		x <= x_.rborder;
		x += g_step.real())
	{
		for(
			real_t y = y_.lborder;
			y <= y_.rborder;
			y += g_step.imag())
		{
			complex_t z(x, y);

			#define CLZ(color) (.5 * std::abs(rborder - lborder) / std::abs(lborder + center_##color - z))
			RGB_COLOR(CLZ(red), CLZ(green), CLZ(blue));

			z = PLOTFUNC(z);
			DisplayPoint(z.real(), z.imag());
		}
	}
}

GFUNC_KEYBOARD {
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
}

GMAIN {
	GFUNC_INIT("graph_i");
}
