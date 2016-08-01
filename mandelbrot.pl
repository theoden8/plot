#!/usr/bin/env perl

use strict;
use warnings;

die if scalar @ARGV != 1;

my($max_iters) = @ARGV;

sub sqr {
	my $n = shift;
	return $n * $n;
}

sub c_cast {
	return ((shift) - $max_iters / 2.) * 4. / $max_iters;
}


# this is dirty
for(my $yy = $max_iters / 4.; $yy < $max_iters * 3./4; ++$yy) {
	for(my $xx = $max_iters / 9.; $xx < $max_iters * 2./3; ++$xx) {
		my ($real, $imag) = (c_cast($xx), c_cast($yy));

		my ($x, $y, $i) = (0., 0., 0);
		while(sqr($x) + sqr($y) <= 4 && $i < $max_iters) {
			my $new_x = sqr($x) - sqr($y) + $real;
			$y = 2. * $x * $y + $imag;
			$x = $new_x;
			++$i;
		}

		print "$xx $yy\n" unless($i >= $max_iters);
	}
}
