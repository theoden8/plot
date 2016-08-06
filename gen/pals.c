#include <stdio.h>
#include <string.h>
#include <assert.h>

#define N 11

#define HALF(len) ((len) >> 1)
#define UHALF(len) (HALF(len) + ((len) & 1))

void finish_left(const char right[], int len) {
	assert(strlen(right) == UHALF(len));
	static half;
	half = HALF(len);
	const char *c = right + half;
	for(int i = 0; i < half; ++i)
		putchar_unlocked(*(c--));
	for(int i = 0; i < 1 + !(len & 1); ++i)
		putchar_unlocked(*c);
	for(int i = 0; i < half; ++i)
		putchar_unlocked(*(++c));
	putchar_unlocked('\n');
}

void next(char right[UHALF(N) + 1], int *len) {
	++*len;
	static rlen;
	rlen = UHALF(*len);
	for(int i = 0; i < rlen - 1; ++i)
		right[i] = '0';

	if(!(*len & 1))
		return;

	right[rlen - 1] = '1';
	right[rlen] = '\0';
}

void iter(char right[UHALF(N) + 1], int len, int i) {
	if(i == -1) {
		finish_left(right, len);
		return;
	}
	assert(strlen(right) > i);
	char init_val = right[i];
	for(char num = init_val; num <= '9'; ++num) {
		right[i] = num;
		iter(right, len, i - 1);
	}
	right[i] = init_val;
}

main() {
	static char right[UHALF(N) + 1];
	static len = 0;
	for(int i = 0; i < N; ++i) {
		next(right, &len);
		iter(right, len, UHALF(len) - 1);
	}
}
