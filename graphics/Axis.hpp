#pragma once

#include "Types.hpp"

struct axis {
	real_t
		winsize,
		gridsize,
		shift,
		thickness;
	real_t
		lborder,
		rborder;
private:
	void reborder();
public:
	axis(real_t winsize, real_t thickness, real_t shift = 0.);
	real_t bold() const;
	void set_grid(real_t diff);
	void set_shift(real_t diff);
	void set_size(real_t newsize);
	bool in_grid(const real_t &val) const;
};
