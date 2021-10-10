#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main (void)
{
	int c;
	time_t t;
	srand((unsigned) time(&t));

	printf("%s\n", (rand() % 2) ? "Heads" : "Tails");

	return 0;
}
