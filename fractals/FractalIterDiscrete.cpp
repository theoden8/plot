#include "FractalIterDiscrete.hpp"

#include "Functions.hpp"

#define JULIA_F(z) (exp(sin(z)))
void JuliaSet::Draw() {
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			complex_t point(x * step, y * step);
			if(!in_plot(point))
				continue;

			complex_t zz(
				(x - width / 2.) * 4. / width,
				(y - height / 2.) * 4. / width
			);
			complex_t z(0., 0.);
			int iter = 0;
			while(iter < level() && std::abs(z) <= 4.) {
				z = JULIA_F(z) + zz;
				++iter;
			}
			if(iter == 0 || iter >= level())
				continue;
			RGB_COLOR((iter < level()) ? (float)iter / level() : 1., 0., 0.);
			G::DisplayPoint(point.real(), point.imag());
		}
	}
}



bool SierpinskiCarpet::point_is_colored(int x, int y) {
	while(x > 0 || y > 0) {
		if(x % 3 == 1 && y % 3 == 1)
			return 1;

		x /= 3;
		y /= 3;
	}
	return 0;
}

void SierpinskiCarpet::Draw() {
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			if(!in_plot(x, y))
				continue;

			bool result = point_is_colored(x, y);
			if(!result)
				continue;

			RGB_COLOR(.0, .0, 1.);
			G::DisplayPoint(x * step, y * step);
		}
	}
}



void SierpinskiTriangle::Draw() {
	static real_t ST3_2 = sqrt(3) / 2.;
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x + y < width; ++x) {
			if(!(x & y) || !in_plot(x, y)) {
				RGB_COLOR(.0, .5, 1.);
				G::DisplayPoint((x + y / 2.) * step, y * step * ST3_2);
			}
		}

	}
}
