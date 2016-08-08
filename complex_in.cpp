#include <cstdio>
#include <vector>

#include "Graphics.hpp"

std::vector <complex_t> data;

GFUNC_DISPLAY {
	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		DisplayPoint(data[i].real(), data[i].imag());
	}
}

GFUNC_KEYBOARD {}

void read_data(std::vector <complex_t> &data) {
	static real_t re, im;
	while(scanf(" %lf %lf", &re, &im) != EOF)
		data.push_back(complex_t(re, im));
}

GMAIN {
	read_data(data);
	GFUNC_INIT("complex_in");
}
