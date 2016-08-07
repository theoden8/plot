#include <cmath>

#include "FractalIterLine.hpp"


static struct turtle {
	complex_t position;
	real_t facing;
};

void go_forward(turtle &t, const real_t &len, const real_t &step) {
	const real_t
		_to_x = cos(t.facing),
		_to_y = sin(t.facing);

	const complex_t u_step(
		step * _to_x,
		step * _to_y
	);

	complex_t i_pos = t.position;
	for(real_t i = 0.; i < len; i += step) {
		i_pos += u_step;
		G::DisplayPoint(i_pos.real(), i_pos.imag());
	}
	t.position += complex_t(
		len * _to_x,
		len * _to_y
	);
}

static enum {
	LEFT = 1,
	RIGHT = -1
} TURN;
static void rotate(turtle &t, const real_t &deg) {
	t.facing += deg;
	while(t.facing > M_PI)
		t.facing -= 2. * M_PI;
	while(t.facing < -M_PI)
		t.facing += 2. * M_PI;
	return;
}

static enum {
	RED, GREEN, BLUE
} COLOR;

static int g_static_id_color = 0;
static void recurse_draw(
	turtle &t,
	const real_t &len,
	const int depth,
	const real_t &step,
	char sign = LEFT
	)
{
	static float colors[] = {
		1., 0., 0.,
		.7, .3, 0.,
		.7, .3, .0,
		.0, 1., .0,
		.0, .7, .3,
		.0, .3, .7,
		.5, .0, .5
	};
	static const real_t
		ST_2 = sqrt(2),
		DEG_45 = M_PI / 4.,
		DEG_90 = M_PI / 2.;

	g_static_id_color = (g_static_id_color == 6) ? 0 : g_static_id_color + 1;
	if(depth == 0) {
		float *col = colors + g_static_id_color * 3;
		RGB_COLOR(col[RED], col[GREEN], col[BLUE]);
		go_forward(t, len, step);
		return;
	}

	rotate(t, DEG_45 * sign * LEFT);
	recurse_draw(t, len / ST_2, depth - 1, step, LEFT);
	rotate(t, DEG_90 * sign * RIGHT);
	recurse_draw(t, len / ST_2, depth - 1, step, RIGHT);
	rotate(t, DEG_45 * sign * LEFT);
}

void DragonCurve::Draw() {
	static turtle t;
	g_static_id_color = 0;
	t.position = complex_t(0., 0.);
	t.facing = 0.;
	recurse_draw(t, std::min(width, height), level(), step);
}
