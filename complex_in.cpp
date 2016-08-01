#include <cstdio>
#include <vector>

#include "glut_config.h"

#include "Graphics.hpp"

std::vector <complex_t> data;

void Graphics::ExtendedDisplay() {
	glColor3f(0.0f,1.0f,0.0f);
	for(real_t i = 0; i < data.size(); ++i) {
		DisplayPoint(data[i].real(), data[i].imag());
	}
}

void Graphics::ExtendedKeyboard(unsigned char key, int x, int y) {
	Keyboard(key);
	Display();
}

void read_data(std::vector <complex_t> &data) {
	static real_t real, imag;
	while(scanf(" %lf %lf", &real, &imag) != EOF)
		data.push_back(complex_t(real, imag));
}

int main(int argc, char *argv[]) {
	read_data(data);
	Graphics::InitOpenGL(&argc, argv, "complex_in");
}
