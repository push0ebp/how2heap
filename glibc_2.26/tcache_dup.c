#include <stdio.h>
#include <stdlib.h>

int main()
{
	fprintf(stderr, "This file demonstrates a simple double-free attack with tcache.\n");

	fprintf(stderr, "Allocating buffer.\n");
	int *a = malloc(8);

	fprintf(stderr, "malloc(8): %p\n", a);
	fprintf(stderr, "Freeing twice...\n");
	free(a);
	free(a);

	fprintf(stderr, "Now the free list has [ %p, %p ].\n", a, a);
	fprintf(stderr, "Next allocated buffers will be same: [ %p, %p ].\n", malloc(8), malloc(8));

	return 0;
}

/*
This file demonstrates a simple double-free attack with tcache.
Allocating buffer.
malloc(8): 0x55fd1aecf260
Freeing twice...
Now the free list has [ 0x55fd1aecf260, 0x55fd1aecf260 ].
Next allocated buffers will be same: [ 0x55fd1aecf260, 0x55fd1aecf260 ].

*/