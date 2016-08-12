#pragma once

#include "Fractal.hpp"

#define LINEAR(NAME) class NAME : public FractalIterLine
FRACTAL(FractalIterLine) {
protected:
	typedef std::pair <complex_t, complex_t> line_t;
	std::vector <line_t> lines_ = {};
	int last_level = level();
	real_t last_size = -1;

	virtual const size_t
		GROW_INIT() = 0,
		GROW_EXP() = 0;
	virtual void
		initialize(),
		reset() = 0,
		increase_level(),
		decrease_level() = 0;
	virtual int make_transform(size_t i) = 0;
public:
};


LINEAR(KochsSnowFlake) {
protected:
	const size_t
		GROW_INIT(),
		GROW_EXP();

	void
		reset(),
		decrease_level();
	int make_transform(size_t i);
public:
	void Draw();
};


FRACTAL(DragonCurve) {
	int color_id = 0;

	typedef struct _turtle {
		complex_t position;
		real_t facing;
	} turtle;

	typedef enum {
		RED, GREEN, BLUE
	} COLOR;

	typedef enum {
		LEFT = 1,
		RIGHT = -1
	} TURN;

	void
		go_forward(turtle &t, const real_t &len),
		rotate(turtle &t, const real_t &deg),
		recurse_draw(turtle &t, const real_t &len, const int depth, char sign = LEFT);
public:
	void Draw();
};
