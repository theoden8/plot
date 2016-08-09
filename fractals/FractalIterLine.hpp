#pragma once

#include "Fractal.hpp"

#define LINEAR(NAME) class NAME : public FractalIterLine
FRACTAL(FractalIterLine) {
protected:
	typedef std::pair <complex_t, complex_t> line_t;
	std::vector <line_t> lines_ = {};
	int last_level = 0;
	real_t last_size = -1;

	virtual const size_t GROW_INIT() = 0;
	virtual const size_t GROW_EXP() = 0;

	virtual void initialize();
	virtual void reset() = 0;
	virtual void increase_level();
	virtual void decrease_level() = 0;
	virtual void make_transform(size_t &i) = 0;
public:
};


LINEAR(KochsSnowFlake) {
protected:
	const size_t GROW_INIT();
	const size_t GROW_EXP();

	void reset();
	void decrease_level();
	void make_transform(size_t &i);
public:
	void Draw();
};


FRACTAL(DragonCurve) {
public:
	void Draw();
};
