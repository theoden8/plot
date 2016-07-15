#include "glut_config.h"

#include <cstdio>
#include <vector>

#include "Graphics.hpp"

std::vector <real_t> data;

void Graphics::ExtendedDisplay() {
	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i)
		DisplayPoint(i, data[i]);
}

void Graphics::ExtendedKeyboard(unsigned char key, int x, int y) {
	Keyboard(key);
	Display();
}


void FillData(std::vector <real_t> &data) {
	real_t value;
	while(scanf("%lf", &value))
		data.push_back(value);
}

int main(int argc, char **argv) {
	FillData(data);
	Graphics::InitOpenGL(&argc, argv, "illustrator");

    return 0;
}
