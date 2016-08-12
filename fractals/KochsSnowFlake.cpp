#include <cmath>
#include <cstdlib>
#include <cassert>

#include "FractalIterLine.hpp"


typedef KochsSnowFlake KSF;


const size_t KSF::GROW_INIT() {
	return 3;
}
const size_t KSF::GROW_EXP() {
	return 4;
}


void KSF::reset() {
	while(level() < 0)
		Keyboard('9');

	if(size() != last_size) {
		if(0 == last_size) {
			last_size = size();
			initialize();
		} else {
			last_size = 0;
			lines_.clear();
			last_level = 0;
			reset();
			return;
		}
	}

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

int KSF::make_transform(size_t i) {
	static const real_t ST_3 = sqrt(3);

	const size_t j = i * GROW_EXP();
	complex_t
		a = lines_[i].first,
		d = lines_[i].second,
		diff = (d - a) / complex_t(3.),
		b = a + diff,
		c = b + diff,
		e = diff;
	const real_t &x = e.real(), &y = e.imag();
	const real_t
		x2 = x * x,
		x3 = x2 * x,
		y2 = y * y,
		y3 = y2 * y;

	e = b + complex_t(
		.5 * (x + ST_3*y),
		(-ST_3*x3 + x2*y + 3.*ST_3*x*y2 - 3.*y3) / (2.*(x2 - 3.*y2))
	);

	lines_[j] = line_t(a, b);
	lines_[j + 1] = line_t(b, e);
	lines_[j + 2] = line_t(e, c);
	lines_[j + 3] = line_t(c, d);

	return 1;
}

void KSF::decrease_level() {
	assert(last_level > 0);

	--last_level;
	size_t new_no_lines = lines_.size() / GROW_EXP();
	for(size_t i = 0; i < new_no_lines; ++i) {
		lines_[i] = lines_[i * GROW_EXP()];
		complex_t
			&a = lines_[i].first,
			&b = lines_[i].second;
		b += complex_t(2.) * (b - a);
	}
	lines_.resize(new_no_lines);
}

void KSF::Draw() {
	reset();
	for(const auto &it : lines_) {
		if(!in_plot(it.first) && !in_plot(it.second))
			continue;

		RGB_COLOR(1., 1., 1.);
		G::DisplayLine(it.first, it.second);
	}
}
