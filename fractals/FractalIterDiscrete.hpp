#pragma once

#include "Fractal.hpp"


#define DISCRETE(NAME) class NAME : public FractalIterDiscrete
FRACTAL(FractalIterDiscrete) {
public:
};


DISCRETE(JuliaSet) {
public:
	void Draw();
};

DISCRETE(SierpinskiCarpet) {
	static bool point_is_colored(int x, int y);
public:
	void Draw();
};

DISCRETE(SierpinskiTriangle) {
	static bool point_is_colored(int x, int y);
public:
	void Draw();
};
