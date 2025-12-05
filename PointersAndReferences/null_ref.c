#include <stdio.h>

void print_value(int *ptr) {
	if (ptr == NULL) {
		printf("Error: NULL pointer!\n");
		return;
	}

	printf("Value: %d\n", *ptr);
}

void print_some_message() {
  printf("2025-12-04");
}

int main() {
	int value = 42;
	int *valid_pointer = &value;
	int *null_pointer = NULL;

	print_value(valid_pointer);
	print_value(null_pointer);

	return 0;
}
