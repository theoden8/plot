#include <cstdio>
#include <vector>

#include "Graphics.hpp"

std::vector <real_t> data;

GFUNC_DISPLAY {
	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i)
		DisplayPoint(i, data[i]);
}

GFUNC_KEYBOARD {}

void read_data(std::vector <real_t> &data) {
	static real_t value;
	while(scanf(" %lf", &value) != EOF)
		data.push_back(value);
}

GMAIN {
	read_data(data);
	GFUNC_INIT("illustrator");
}
