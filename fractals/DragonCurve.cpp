#include <cmath>

#include "FractalIterLine.hpp"


void DragonCurve::go_forward(turtle &t, const real_t &len) {
	complex_t new_position = t.position + complex_t(
		cos(t.facing),
		sin(t.facing)
	) * len;

	G::DisplayLine(t.position, new_position);

	t.position = new_position;
}

void DragonCurve::rotate(turtle &t, const real_t &deg) {
	t.facing += deg;
	while(t.facing > M_PI)
		t.facing -= 2. * M_PI;
	while(t.facing < -M_PI)
		t.facing += 2. * M_PI;
	return;
}

void DragonCurve::recurse_draw(turtle &t, const real_t &len, const int depth, char sign) {
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

	color_id = (color_id == 6) ? 0 : color_id + 1;
	if(depth == 0) {
		float *col = colors + color_id * 3;
		RGB_COLOR(col[RED], col[GREEN], col[BLUE]);
		go_forward(t, len);
		return;
	}

	rotate(t, DEG_45 * sign * LEFT);
	recurse_draw(t, len / ST_2, depth - 1, LEFT);
	rotate(t, DEG_90 * sign * RIGHT);
	recurse_draw(t, len / ST_2, depth - 1, RIGHT);
	rotate(t, DEG_45 * sign * LEFT);
}

void DragonCurve::Draw() {
	static turtle t;
	color_id = 0;
	t.position = complex_t(0., 0.);
	t.facing = 0.;
	recurse_draw(t, std::min(width, height), level());
}
