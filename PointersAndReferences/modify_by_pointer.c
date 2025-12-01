#include <stdio.h>

void divide_with_reminder(int dividend, int divisor, int *quotient, int *reminder){
	if (quotient != NULL) {
		*quotient = dividend / divisor;
	}

	if (reminder != NULL) {
		*reminder = dividend % divisor;
	}
}

int main() {
	int q, r;

	divide_with_reminder(23, 4, &q, &r);

	printf("23 / 4 = %d reminder %d\n", q, r);

	return 0;
}
