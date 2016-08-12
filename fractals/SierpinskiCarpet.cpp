#include "FractalIterDiscrete.hpp"


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

			RGB_COLOR(.0, .0, 1.);
			G::DisplayPoint(step * x, step * y);
		}
	}
}
