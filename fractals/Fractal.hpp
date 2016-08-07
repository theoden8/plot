#pragma once

#include <vector>

#include "Types.hpp"
#include "Graphics.hpp"

typedef Graphics G;


#define X G::x()
#define Y G::y()

#define FRACTAL(NAME) class NAME : public Fractal
class Fractal {
	int level_ = 1;
protected:
	real_t
		step = 50.,
		width = step,
		height = step;

	void change_step(const real_t &diff);
	bool in_plot(const real_t &x, const real_t &y) const;
	bool in_plot(const complex_t &z) const;
public:
	Fractal();
	~Fractal();

	int level() const;

	virtual void Keyboard(char key);
	virtual void Draw() = 0;
};

#undef X
#undef Y
