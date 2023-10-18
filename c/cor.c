/**
 * Written by: https://github.com/bojle
 * License: Do whatever you want to
 **/
#include <stdio.h>
#include <stdlib.h>

/* Chain of Responsilbity */

/* To compile:
 * 		gcc cor.c -o a -Wno-incompatible-pointer-types
 */

/* 'Request' here is the addition, subtraction, multiplication
 * or division of two integers. The purpose of this module
 * is to show how the Chain of Responsibility pattern from 
 * Gang Of Four Design Pattern book.
 */

typedef enum {
	ADD,
	SUB,
	MUL,
	DIV,
	NULLM		/* NULLMethod: Denotes the method that will be called when
				   a request falls off the chain */
} Type;

/* Function Pointer type that represents the 'methods' */
/* Parameters:
 * 		int *: Is supposed to be a Chain *. Becomes Chain*
 * 		through implicity type conversion.
 *
 *		Type: Allows a method to decide if the two numbers
 *		are to be handled by itself or by another method in
 *		the chain.
 *
 *		int, int: The two numbers to be operated.
 */
typedef int (*fptr) (int *, Type, int, int);

typedef struct {
	Type type;
	struct Chain *next;
	fptr operate;
} Chain;

/* Associate a Chain object with its next chain object,
 * with its type and its method
 */
void make_chain(Chain *c, Type t, Chain *next, fptr op) {
	c->type = t;
	c->next = next;
	c->operate = op;
}

/* Auxillary Function */
int operate_chain(Chain *c, Type t, int a, int b) {
	return (c->operate)(c, t, a, b);
}

int add_method(Chain *c, Type t, int a, int b) {
	/* If requested method is not "Add these numbers", defer the
	 * request to the next object in the chain
	 */
	if (c->type != t) {
		Chain *next = c->next;
		(next->operate)(next, t, a, b);
	}
	else {
		return a+b;
	}
}

int sub_method(Chain *c, Type t, int a, int b) {
	if (c->type != t) {
		Chain *next = c->next;
		(next->operate)(next, t, a, b);
	}
	else {
		return a-b;
	}
}

int mul_method(Chain *c, Type t, int a, int b) {
	if (c->type != t) {
		Chain *next = c->next;
		(next->operate)(next, t, a, b);
	}
	else {
		return a*b;
	}
}

int div_method(Chain *c, Type t, int a, int b) {
	if (c->type != t) {
		Chain *next = c->next;
		(next->operate)(next, t, a, b);
	}
	else {
		if (b != 0) {
			return a/b;
		}
	}
}

int null_method(Chain *c, Type t, int a, int b) {
	/* Raise exceptions */
}

int main() {
	Chain c1;
	Chain c2;
	Chain c3;
	Chain c4;
	Chain c5;

	/* Potential drawback: The chain has to be manually contructed
	 * and the terminal condition (null_method) has to be declared
	 * explicitly
	 */
	make_chain(&c1, ADD, &c2, add_method);
	make_chain(&c2, SUB, &c3, sub_method);
	make_chain(&c3, MUL, &c4, mul_method);
	make_chain(&c4, DIV, &c5, div_method);
	make_chain(&c5, NULLM, NULL, null_method);

	/* Should call mul_method */
	printf("Multiplication: %d\n", operate_chain(&c1, MUL, 4, 5));
	/* Request is slipped off the chain as after c2 in
	 * the chain, no other functions accept ADD */
	printf("Addition: %d\n", operate_chain(&c2, ADD, 4, 5));
	/* Works just fine; output: 0 */
	printf("Division: %d\n", operate_chain(&c1, DIV, 4, 5));
	/* 151 is an unknown request - slipped off the chain */
	printf("Unknown: %d\n", operate_chain(&c1, 151, 4, 5));
}

#if 0
	PS: This code breaks encapsulation. main() has access to all the elements of
	Chain object when it shouldn't. Can be fixed by moving all the 'chain' code'
	into a separate file and making all of it static.
#endif
