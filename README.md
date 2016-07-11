# Plot

## Authors

Created by Kirill Rodriguez somewhen between 2014-2015.

## Program

### Purpose

Visualization (own tiny mathematical toolchain).

### Description

#### illustrator

Takes a sequence of points from **stdin** and plots on a graph.

#### graph

Generates a sequence of points from a hardcoded function and plots on a graph.

### State

Because it was formerly two repositories which shared many lines of code, they became one repository with 2 binaries, and during the code recomposition runtime viability of the program graph was lost.

### Bugs / Errors

For problems on compilation or runtime stage you are always welcome to raise an issue (in case the program is promised to work, but its not).

## Installation

### Prerequisites

* cmake
* make
* gcc/clang
* glut

### Compiling

	cmake .
	make

## Usage

	./_illustrator # (< file|<<EOF|<<<$(command)) stdin
	
----
	
	$EDITOR graph.cpp # edit calc functino and char *function (function name)
	make
	./_graph

## Disclaimer

Written in a quick-and-dirty way. Use at own risk.