# Plot

## Authors

Created by Kirill Rodriguez somewhen between 2014-2015.

## Program

### Purpose

Tiny plotting utilities that are handy for visualising numbers and exploring mathematical functions.

### Description

#### illustrator

Plots a sequence of points from **stdin**.

#### graph

Plots a hardcoded function.

### Bugs / Errors

For problems on compilation or runtime stage you are always welcome to raise an issue.

## Installation

### Prerequisites

* cmake
* make
* gcc/clang
* GLUT

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