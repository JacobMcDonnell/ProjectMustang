#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main (void)
{
	int sides = 6;
	time_t t;
	srand((unsigned) time(&t));

	printf("%d\n", (rand() % sides) + 1);

	return 0;
}