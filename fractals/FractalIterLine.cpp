#include <cassert>
#include <cmath>
#include <cstdlib>

#include "FractalIterLine.hpp"

typedef FractalIterLine FrctLine;

void FrctLine::initialize() {
	assert(GROW_INIT() > 0 && GROW_INIT() != 2);

	const real_t
		half = size() / 2.;
	std::vector <complex_t> verts;
	if(GROW_INIT() == 1) {
		verts = {
			{-half, half}
		};
	} else {
		static complex_t last_vert;
		real_t degree = .5 * M_PI;

		for(int i = 0; i < GROW_INIT(); ++i) {
			const complex_t new_vert(cos(degree) * half, sin(degree) * half);

			if(i > 0)
				lines_[i] = { last_vert, new_vert };

			degree += (M_PI / (real_t)GROW_INIT());
			last_vert = new_vert;
		}
	}
}

void FrctLine::increase_level() {
	++last_level;

	size_t old_no_lines = lines_.size();
	lines_.resize(old_no_lines * GROW_EXP());

	size_t i = old_no_lines - 1;
	while(i != (size_t)-1)
		make_transform(i);
}
