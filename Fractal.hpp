#pragma once

#include <functional>
#include <vector>
#include "glut_config.h"

#include "Types.hpp"
#include "Graphics.hpp"

typedef Graphics G;

#define X G::x()
#define Y G::y()


#define FRACTAL(NAME) class NAME : public Fractal
class Fractal {
	int level_ = 1;
protected:
	real_t step = 50., width = X.rborder / step, height = Y.rborder / step;

	void change_step(real_t diff) {
		real_t
			act_w = width * step,
			act_h = height * step;
		step *= diff;
		width = act_w / step;
		height = act_h / step;
	}
public:
	Fractal() {}
	~Fractal() {}

	#define FRACTAL_DRAW Draw(const std::function <void (complex_t, float, float, float)> &per_point)
	virtual void FRACTAL_DRAW = 0;


	int level() {
		return level_;
	}

	virtual void Keyboard(char key) {
		static real_t
			increase = 1.05,
			decrease = 1/increase;
		switch(key) {
			case '-':
				change_step(decrease);
			break;
			case '=':
				change_step(increase);
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

			case '0':
				if(level_)
					--level_;
			break;
			case '9':
				++level_;
			break;
		}
	}
};

#define DISCRETE(NAME) class NAME : public FractalIterDiscrete
FRACTAL(FractalIterDiscrete) {
protected:
	bool in_plot(int x, int y) {
		x *= step;
		y *= step;
		return (x >= X.lborder && x <= X.rborder && y >= Y.lborder && y <= Y.rborder);
	}
public:
};

DISCRETE(MandelbrotSet) {
public:
	void FRACTAL_DRAW;
};

DISCRETE(SierpinskiCarpet) {
	static bool point_is_colored(int x, int y);

public:
	void FRACTAL_DRAW;
};

DISCRETE(SierpinskiTriangle) {
	static bool point_is_colored(int x, int y);

public:
	void FRACTAL_DRAW;
};


FRACTAL(KochsFlake) {
protected:
	typedef std::pair <complex_t, complex_t> line_t;
	std::vector <line_t> lines_ = {};
	int last_level = 0;
	real_t last_size = -1;

	real_t size() const;
	void reset();
	void increase_level();
	bool in_plot(complex_t z) {
		real_t x = z.real(), y = z.imag();
		return (x >= X.lborder && x <= X.rborder && y >= Y.lborder && y <= Y.rborder);
	}
public:
	void FRACTAL_DRAW;
};

#undef X
#undef Y
#undef FRACTAL
#undef DISCRETE
