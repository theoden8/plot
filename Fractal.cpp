#include <cmath>
#include <assert.h>

#include "Fractal.hpp"
#include "Types.hpp"


void MandelbrotSet::FRACTAL_DRAW {
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
			per_point(
				complex_t(xx * step, yy * step),
				(iter < level()) ? (float)iter / level() : 1., 0., 0.
			);
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

void SierpinskiCarpet::FRACTAL_DRAW {
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			if(!in_plot(x, y))
				continue;

			bool result = point_is_colored(x, y);
			if(!result)
				continue;
			per_point(
				complex_t(x * step, y * step),
				0., 0., 1.
			);
		}
	}
}



void SierpinskiTriangle::FRACTAL_DRAW {
	static real_t ST3_2 = sqrt(3) / 2.;
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x + y < width; ++x) {
			if(!(x & y) || !in_plot(x, y)) {
				per_point(
					complex_t((x + y / 2.) * step, y * step * ST3_2 ),
					0., .5, 1.
				);
			}
		}

	}
}



real_t KochsFlake::size() const {
	return std::min(width, height);
}

static real_t no_lines(int level) {
	assert(level >= 0);

	static int sizes[] = {
		3, 12, 48, 196, 768, 3072, 12288
	};

	if(level < 7)
		return sizes[level];
	return 3 * pow(4, level);
}

void KochsFlake::reset() {
	if(size() != last_size) {
		if(0 == last_size) {
			last_size = size();
			lines_.resize(no_lines(last_level));

			real_t
				half = size() / 2.,
				top = half * sqrt(3);
			lines_[0] = line_t(complex_t(0, 0), complex_t(size(), 0));
			lines_[1] = line_t(complex_t(half, top), complex_t(0, 0));
			lines_[2] = line_t(complex_t(size(), 0), complex_t(half, top));
		} else {
			last_size = 0;
			lines_.clear();
			last_level = 0;
			reset();
			return;
		}
	}

	while(level() < 0)
		Keyboard('9');

	if(level() >= last_level) {
		if(level() == last_level)
			return;

		for(int i = last_level; i < level(); ++i)
			increase_level();

		last_level = level();
	} else {
		last_level = 0;
		last_size = 0;
		reset();
		return;
	}
}

void KochsFlake::increase_level() {
	++last_level;

	lines_.resize(no_lines(last_level));
	size_t old_no_lines = no_lines(last_level - 1);
	for(size_t i = old_no_lines - 1; i != (size_t)-1; --i) {
		size_t j = i << 2;
		complex_t
			a = lines_[i].first,
			d = lines_[i].second,
			diff = (d - a) / complex_t(3.),
			b = a + diff,
			c = b + diff,
			e = diff;
		const real_t &x = e.real(), &y = e.imag();
		const real_t
			ST3 = sqrt(3),
			x2 = x * x,
			x3 = x2 * x,
			y2 = y * y,
			y3 = y2 * y;

		e = b + complex_t(
			.5 * (x + ST3*y),
			(-ST3*x3 + x2*y + 3.*ST3*x*y2 - 3.*y3) / (2.*(x2 - 3.*y2))
		);

		lines_[j] = line_t(a, b);
		lines_[j + 1] = line_t(b, e);
		lines_[j + 2] = line_t(e, c);
		lines_[j + 3] = line_t(c, d);
	}
}

void KochsFlake::FRACTAL_DRAW {
	reset();
	printf("%lu\n", sizeof(line_t) * lines_.size());
	for(const auto &it : lines_) {
		complex_t linestep = (it.second - it.first) / step;
		for(real_t i = 0; i < step; ++i) {
			complex_t point = it.first + linestep * i;

			if(!in_plot(point))
				continue;

			per_point(
				point,
				1., .0, .0
			);
		}
	}
}
