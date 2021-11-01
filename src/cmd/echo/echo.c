#include <stdio.h>
#include <string.h>

int
main (int argc, char *argv[])
{
	int i, nflag = 0;
	argc--;

	for (i = 1; i <= argc; i++) {
		if (strcmp(argv[i], "-n") == 0)
			nflag++;
		else
			printf("%s%c", argv[i], (i == argc) ? ((nflag == 1) ? '\0' : '\n') : ' ');
	}
	return 0;
}