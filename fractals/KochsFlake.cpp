#include <Cmath>
#include <cstdlib>
#include <cassert>

#include "FractalIterLine.hpp"


size_t KochsFlake::no_lines(int level) {
	assert(level >= 0);

	static size_t sizes[] = {
		3, 12, 48,
        196,
        768,
        3072,
		12288,
		49152,
		196608,
		786432,
		3145728,
		12582912,
		50331648,
		201326592,
		805306368,
		3221225472,
		12884901888,
		51539607552,
		206158430208,
		824633720832
	};

	if(level < 20)
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
				top3 = half * sqrt(3),
                top = top3/3.;
			lines_[0] = line_t(complex_t(-half, -top), complex_t(half, -top));
			lines_[2] = line_t(complex_t(half, -top), complex_t(0., top * 2.));
			lines_[1] = line_t(complex_t(0., top * 2.), complex_t(-half, -top));
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

	if(level() == last_level) {
		return;
	} else if(level() >= last_level) {
		for(int i = last_level; i < level(); ++i)
			increase_level();

		last_level = level();
	} else {
		for(int i = level(); i < last_level; ++i)
			decrease_level();

		last_level = level();
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

void KochsFlake::decrease_level() {
	--last_level;
	size_t new_no_lines = no_lines(last_level - 1);
	for(size_t i = 0; i < new_no_lines - 1; ++i) {
		lines_[i] = lines_[i << 2];
		lines_[i].first *= 3.;
		lines_[i].second *= 3.;
	}
	lines_.resize(new_no_lines);
}

void KochsFlake::Draw() {
	reset();
	for(const auto &it : lines_) {
		if(!in_plot(it.first) && !in_plot(it.second))
			continue;

		RGB_COLOR(1., 1., 1.);
		G::DisplayLine(
			it.first,
			it.second,
			std::abs(step / 10.)
		);
	}
}
