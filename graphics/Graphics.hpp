#pragma once

#include <stdarg.h>
#include "include/glut_config.h"

#include "Types.hpp"
#include "Axis.hpp"

#include <stdio.h>

class Graphics {
	static axis x_, y_;
public:
	const static axis &x() { return x_; }
	const static axis &y() { return y_; }
	#define GMAIN int main(int argc, char *argv[])
	#define GFUNC_INIT(NAME) Graphics::InitGLUT(&argc, argv, NAME)
	static void InitGLUT(int *argc, char **argv, const char *name);
private:
	static void Display();

	//GraphicsDisplay
	static void DisplayText(real_t x, real_t y, const char *fmt, ...);
	static void DisplayVariables();
	static void DisplayAxis();

public:
	#define RGB_COLOR(R, G, B) glColor3f(R, G, B)
	static inline void DisplayPoint(const complex_t &z) {
		DisplayPoint(z.real(), z.imag());
	}
	static void DisplayPoint(const real_t &x, const real_t &y);
	static void DisplayLine(const complex_t &start, const complex_t &fin);
private:
	//GraphicsFuncs
	static void Reshape(int new_size_x, int new_size_y);
	static void GeneralKeyboard(unsigned char key, int x, int y);
	static void Keyboard(unsigned char key);
	static void Special(int key, int x, int y);

	//defined within a project
	#define GFUNC_DISPLAY void Graphics::ExtendedDisplay()
	#define GFUNC_KEYBOARD void Graphics::ExtendedKeyboard(unsigned char key)
	static void ExtendedDisplay();
	static void ExtendedKeyboard(unsigned char key);
};
