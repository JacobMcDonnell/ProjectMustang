#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int coinFlip (int times);

int
main (int argc, char *argv[])
{
	int nflag = 0, i, times = 1, tails, heads;
	argc--;

	for (i = 1; i <= argc; i++) {
		if (strcmp(argv[i], "-n") == 0)
			nflag++;
		else if (nflag == 1)
			times = atoi(argv[i]);
			if (times == 0) {
				printf("Non Integer Value Inputted\n");
				return -1;
			}
	}
	if (times == 1)
		printf("%s\n", coinFlip(times) ? "Heads" : "Tails");
	else {
		tails = coinFlip(times);
		heads = times - tails;
		float ph = (float)heads/times, pt = (float)tails/times;

		printf("Heads: %d\nTails: %d\nProb Heads: %f\nProb Tails: %f\n", heads, tails, ph, pt);
	}

	return 0;
}

/* coinFlip: Flips a coin n numbers of times and returns the number of tails */
int
coinFlip (int times)
{
	int tails, i, c;
	time_t t;
	srand((unsigned) time(&t));

	tails = 0;

	for (i = 0; i < times; i++) {
		c = rand() % 2;
		if (c == 1)
			tails++;
	}

	return tails;
}