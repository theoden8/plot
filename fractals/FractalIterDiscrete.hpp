#pragma once

#include "Fractal.hpp"


// for this class change_step must be changed with the dimensions as
// { F: x -> x * step } is a morphism from discrete grid to real grid
#define DISCRETE(NAME) class NAME : public FractalIterDiscrete
FRACTAL(FractalIterDiscrete) {
protected:
	void change_step(const real_t &diff);
};


DISCRETE(JuliaSet) {
public:
	using FractalIterDiscrete::FractalIterDiscrete;
	void Draw();
};

DISCRETE(SierpinskiCarpet) {
	static bool point_is_colored(int x, int y);
public:
	using FractalIterDiscrete::FractalIterDiscrete;
	void Draw();
};

DISCRETE(SierpinskiTriangle) {
	static bool point_is_colored(int x, int y);
public:
	using FractalIterDiscrete::FractalIterDiscrete;
	void Draw();
};
