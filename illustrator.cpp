#include <cstdio>
#include <vector>

#include "glut_config.h"

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


void read_data(std::vector <real_t> &data) {
	static real_t value;
	while(scanf(" %lf", &value) != EOF)
		data.push_back(value);
}

int main(int argc, char **argv) {
	read_data(data);
	Graphics::InitOpenGL(&argc, argv, "illustrator");
}
