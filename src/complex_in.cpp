#include <cstdio>
#include <vector>

#include "Graphics.hpp"
#include "Data.hpp"

std::vector <complex_t> data;

GFUNC_DISPLAY {
	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		DisplayPoint(data[i]);
	}
}

GFUNC_KEYBOARD {}

GMAIN {
	read_data(data);
	GFUNC_INIT("complex_in");
}
