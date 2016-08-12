#include <cassert>
#include <cmath>
#include <cstdlib>

#include "FractalIterLine.hpp"

typedef FractalIterLine FrctLine;

void FrctLine::initialize() {
	assert(GROW_INIT() > 0 && GROW_INIT() != 2);

	lines_.resize(GROW_INIT());

	const real_t
		half = size() / 2.;
	if(GROW_INIT() == 1) {
		lines_[0] = line_t(complex_t(-half, 0), complex_t(half, 0));
	} else {
		static std::vector <complex_t> verts;
		static complex_t last_vert;
		real_t degree = 0.;
		const real_t
			dstep = (2. * M_PI / (real_t)(GROW_INIT()));

		for(size_t i = 0; i < GROW_INIT(); ++i) {
			const complex_t new_vert(cos(degree) * half, sin(degree) * half);

			if(i > 0)
				lines_[i] = { last_vert, new_vert };

			degree += dstep;
			last_vert = new_vert;
		}

		lines_[0] = line_t(last_vert, lines_[1].first);
	}
}

void FrctLine::increase_level() {
	++last_level;

	size_t old_no_lines = lines_.size();
	lines_.resize(old_no_lines * GROW_EXP());

	size_t i = old_no_lines - 1;
	while(i != (size_t)-1) {
		i -= make_transform(i);
	}
}
