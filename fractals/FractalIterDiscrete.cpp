#include "FractalIterDiscrete.hpp"

#include "Functions.hpp"


typedef FractalIterDiscrete FrctDiscr;


void FrctDiscr::change_step(const real_t &diff) {
	const real_t
		act_w = width * step,
		act_h = height * step;
	step *= diff;
	width = act_w / step;
	height = act_h / step;
}
