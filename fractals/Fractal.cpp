#include <cmath>
#include <assert.h>

#include "Fractal.hpp"

#define X G::x()
#define Y G::y()


void Fractal::change_step(const real_t &diff) {
	const real_t
		act_w = width * step,
		act_h = height * step;
	step *= diff;
	/* width = act_w / step; */
	/* height = act_h / step; */
}


bool Fractal::in_plot(const real_t &x, const real_t &y) const {
	return X.in_grid(x) && Y.in_grid(y);
}

bool Fractal::in_plot(const complex_t &z) const {
	return in_plot(z.real(), z.imag());
}


Fractal::Fractal()
{}

Fractal::~Fractal() {
}


int Fractal::level() const {
	return level_;
}


void Fractal::Keyboard(const char key) {
	static real_t
		increase = 1.05,
		decrease = 1/increase;
	switch(key) {
		case '-':
			change_step(decrease);
		break;
		case '=':
			change_step(increase);
		break;
		case 'h':
			width *= decrease;
		break;
		case 'j':
			height *= decrease;
		break;
		case 'k':
			height = height * increase + 1;
		break;
		case 'l':
			width = width * increase + 1;
		break;

		case '0':
			if(level_)
				--level_;
		break;
		case '9':
			++level_;
		break;
	}
}


#undef X
#undef Y
