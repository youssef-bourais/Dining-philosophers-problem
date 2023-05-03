
#include <stdio.h>
#include <stdlib.h>

typedef struct b b_b;

typedef struct a
{
	int some_number;
	b_b *struct_b;

} a_a;

typedef struct b
{
	int x;
	int z;
	a_a *struct_a;
} b_b;

a_a func(void)
{
	a_a test;
	test.some_number = 310;
	return test;
}

void funct_test2(b_b *b_test)
{

	printf("%d\n", b_test->struct_a->some_number);
}

// void func_test(a_a *a)
// {
// 	b_b *b;
// 	b = malloc(sizeof(b_b) * a->some_number);

// 	funct_test2(b);

// }

void func_test(a_a *a) {
    b_b *b = malloc(sizeof(b_b) * a->some_number);

    for (int i = 0; i < a->some_number; i++) {
        b[i].struct_a = malloc(sizeof(a_a));
        *b[i].struct_a = func(); // initialize struct_a with a new a_a struct
    }

    funct_test2(&b[0]);
}

int main()
{
	a_a hi;
	hi = func();
	func_test(&hi);
}