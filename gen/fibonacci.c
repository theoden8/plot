#include <stdio.h>
#include <string.h>

#define N 50

#define INT unsigned long long

// 2x2 *=
void mul_eq(INT dest[4], const INT b[4]) {
	static INT a[4];
	memcpy(a, dest, sizeof(INT) * 4);

	dest[0] = a[0] * b[0] + a[1] * b[2];
	dest[1] = a[0] * b[1] + a[1] * b[3];
	dest[2] = a[2] * b[0] + a[3] * b[2];
	dest[3] = a[2] * b[1] + a[3] * b[3];
}

#define PRINT(mat) printf("%llu %llu\n%llu %llu\n", mat[0], mat[1], mat[2], mat[3])

main() {
	// [[1, 1], [1, 0]] ** 3
	static const INT F_3[] = {
		3, 2,
		2, 1
	};
	static INT exp_mat[4];
	memcpy(exp_mat, F_3, sizeof(INT) * 4);

	printf("%d\n%d\n%d\n%d\n", 1, 1, 2, 3);
	for(int i = 0; i < N - 4; i += 3) {
		mul_eq(exp_mat, F_3);
		printf("%llu\n%llu\n%llu\n",
				exp_mat[3],
				exp_mat[1],
				exp_mat[0]
		);
	}
}
