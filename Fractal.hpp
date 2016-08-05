#pragma once

#include <functional>
#include "glut_config.h"

#include "Types.hpp"
#include "Graphics.hpp"

typedef Graphics G;

#define FRACTAL(NAME) class NAME : public Fractal
class Fractal {
	int level_ = 3;
public:
	Fractal() {}
	~Fractal() {}

	#define FRACTAL_DRAW Draw(const std::function <void (complex_t, float, float, float)> &per_point)
	virtual void FRACTAL_DRAW = 0;


	int level() {
		return level_;
	}

	void incr() {
		++level_;
	}

	void decr() {
		--level_;
	}
};

#define X Graphics::x()
#define Y Graphics::y()

#define DISCRETE(NAME) class NAME : public FractalIterDiscrete
FRACTAL(FractalIterDiscrete) {
protected:
	int step = 50, width = (int)X.gridsize >> 1, height = (int)Y.gridsize >> 1;

	bool in_plot(int x, int y) {
		return (x >= X.lborder && x <= X.rborder && y >= Y.lborder && y <= Y.rborder);
	}
public:
	virtual void Keyboard(char key) {
		static float
			increase = 1.05,
			decrease = 1/increase;
		switch(key) {
			case '-':
				step = step * decrease;
				if(!step)
					step = 1;
			break;
			case '=':
				step = step * increase + 1;
			break;
			case 'h':
				width *= decrease;
			break;
			case 'j':
				height *= decrease;
			break;
			case 'k':
				height = height * increase + 1;
			break;
			case 'l':
				width = width * increase + 1;
			break;
		}
	}
};

DISCRETE(MandelbrotSet) {
public:
	void FRACTAL_DRAW;
};

DISCRETE(SierpinskyCarpet) {
	static bool pixel_is_filled(int x, int y);

public:
	void FRACTAL_DRAW;
};

#undef X
#undef Y
#undef FRACTAL
#undef DISCRETE
