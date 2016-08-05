#include "Fractal.hpp"
#include "Types.hpp"


void MandelbrotSet::FRACTAL_DRAW {
	for(int yy = 0; yy < height; yy += step) {
		for(int xx = 0; xx < width; xx += step) {
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
			per_point(
				complex_t(xx, yy),
				(iter < level()) ? (float)iter / level() : 1., 0., 0.
			);
		}
	}
}



bool SierpinskyCarpet::pixel_is_filled(int x, int y) {
	while(x > 0 || y > 0) {
		if(x % 3 == 1 && y % 3 == 1)
			return 1;

		x /= 3;
		y /= 3;
	}
	return 0;
}

void SierpinskyCarpet::FRACTAL_DRAW {
	for(int y = 0; y < height; y += step) {
		for(int x = 0; x < width; x += step) {
			if(!in_plot(x, y))
				continue;

			bool result = pixel_is_filled(x, y);
			if(!result)
				continue;
			per_point(
				complex_t(x, y),
				1., 0., 0.
			);
		}
	}
}
