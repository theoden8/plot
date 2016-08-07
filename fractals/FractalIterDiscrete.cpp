#include "FractalIterDiscrete.hpp"


void MandelbrotSet::Draw() {
	for(int yy = 0; yy < height; ++yy) {
		for(int xx = 0; xx < width; ++xx) {
			if(!in_plot(xx, yy))
				continue;

			complex_t zz(
				(xx - width / 2.) * 4. / width,
				(yy - height / 2.) * 4. / width
			);
			complex_t z(0., 0.);
			int iter = 0;
			while(z.real() * z.real() + z.imag() * z.imag() <= 4. && iter < level()) {
				z = z * z + zz;
				++iter;
			}
			if(iter == 0 || iter >= level())
				continue;
			G_COLOR((iter < level()) ? (float)iter / level() : 1., 0., 0.);
			G::DisplayPoint(xx * step, yy * step);
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

			G_COLOR(.0, .0, 1.);
			G::DisplayPoint(x * step, y * step);
		}
	}
}



void SierpinskiTriangle::Draw() {
	static real_t ST3_2 = sqrt(3) / 2.;
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x + y < width; ++x) {
			if(!(x & y) || !in_plot(x, y)) {
				G_COLOR(.0, .5, 1.);
				G::DisplayPoint((x + y / 2.) * step, y * step * ST3_2);
			}
		}

	}
}
