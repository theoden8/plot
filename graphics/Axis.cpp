#include "Axis.hpp"

void axis::reborder() {
	lborder = -gridsize / 2. + shift;
	rborder = gridsize / 2. + shift;
}

axis::axis(real_t winsize, real_t thickness, real_t shift):
	winsize(winsize), gridsize(winsize * 4), thickness(thickness), shift(shift),
	lborder(-gridsize/2. + shift), rborder(gridsize/2. + shift)
{}

real_t axis::bold() const {
	return thickness * gridsize / winsize;
}

void axis::set_grid(real_t diff) {
	gridsize *= diff;
	reborder();
}

void axis::set_shift(real_t diff) {
	shift += gridsize * (diff - 1);
	reborder();
}

void axis::set_size(real_t newsize) {
	set_grid(newsize / winsize);
	winsize = newsize;
}

bool axis::in_grid(const real_t &val) const {
	return lborder <= val && val <= rborder;
}
