#include <cassert>

#include "FractalIterDiscrete.hpp"

/* #define JULIA_F(z, c) (exp(sin(z + zz))) */
/* #define JULIA_HACK_C(c) 4. */
#define JULIA_F(z, c) (z * z + c)
#define JULIA_HACK_C(c) (sinh(cosh(c)))


void JuliaSet::Draw() {
	const complex_t
		half(ceil(width/2.), floor(height/2.)),
		left(
			ceil(std::max(-half.real(), G::x().lborder / step)),
			floor(std::max(-half.imag(), G::y().lborder / step))),
		right(
			ceil(std::min(half.real(), G::x().rborder / step)),
			floor(std::min(half.imag(), G::y().rborder / step))),
		ldiff = left - half,
		rdiff = half - right;

	for(int y = left.imag(); y < right.imag(); ++y) {
		for(int x = left.real(); x < right.real(); ++x) {
			complex_t point = complex_t(x, y) * step;

			const complex_t zz = complex_t(x, y) * (2. / half.real());
			complex_t z(0., 0.);
			int iter = 0;
			while(iter < level() && std::abs(z) <= std::abs(JULIA_HACK_C(zz))) {
				z = JULIA_F(z, zz);
				++iter;
			}
			if(iter == 0 || iter >= level())
				continue;
			RGB_COLOR((iter < level()) ? (float)iter / level() : 1., 0., 0.);
			G::DisplayPoint(point.real(), point.imag());
		}
	}
}
