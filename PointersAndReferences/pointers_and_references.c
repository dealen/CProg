#include <stdio.h>


void add_and_print(int a){
	int a_original_value = a;
	a = a + 1;
	printf("Output equals [%d] which is input [%d] plus 1.\n", a, a_original_value); 
}

void add_and_print_but_with_ptr(int *a){
	int a_original_value = *a;
	*a = *a + 1;
	printf("Output equals [%d] which is input [%d] plus 1.\n", *a, a_original_value);
}

typedef struct {
	char name[50];
	int age;
} Person;

void make_older_copy(Person p) {
	p.age += 1;
	printf("Inside function: %s is %d\n", p.name, p.age);
}

void make_older_ptr(Person *p){
	
	if (p == NULL){
		printf("Error: Null pointer!");
		return;
	}

	p->age += 1;
	printf("Inside function: %s is %d\n", p->name, p->age);
}

int main() {
	int a = 9;
	add_and_print(a);
	printf("a after modification by add_and_print = %d\n", a);

	add_and_print_but_with_ptr(&a);
	printf("a after modification by add_and_print_but_with_ptr = %d\n", a);

	printf("================================================");

	Person john = {"John", 30};
	printf("\nOriginal: %s is %d\n", john.name, john.age);

	make_older_copy(john);
	printf("After copy: %s is %d\n", john.name, john.age);

	make_older_ptr(&john);
	printf("After ptr: %s is %d\n", john.name, john.age);

	Person kuba;
	make_older_ptr(&kuba);

	return 0;
}


