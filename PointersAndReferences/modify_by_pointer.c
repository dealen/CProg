#include <stdio.h>

void divide_with_remainder(int dividend, int divisor, int *quotient, int *remainder){
	if (quotient != NULL) {
		*quotient = dividend / divisor;
	}

	if (remainder != NULL) {
		*remainder = dividend % divisor;
	}
}

int main() {
	int q, r;

	divide_with_remainder(23, 4, &q, &r);

	printf("23 / 4 = %d remainder %d\n", q, r);

	return 0;
}
