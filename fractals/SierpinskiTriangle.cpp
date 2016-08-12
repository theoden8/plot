#include "FractalIterDiscrete.hpp"


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
