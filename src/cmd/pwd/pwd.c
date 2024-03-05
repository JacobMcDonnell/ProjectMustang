#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define MAXLEN	1024

/* print the current working directory */
int main(void)
{
	char *cwd, i = 1;

	do {
		size_t size = i * MAXLEN;
		cwd = (char *)malloc(size);
		getcwd(cwd, size);
		if (errno == ERANGE)
			free((void *)cwd);
	} while (errno == ERANGE && ++i < 10);

	if (errno == ERANGE) {
		fprintf(stderr, "pwd: directory name is too large\n");
		return -1;
	}

	printf("%s\n", cwd);
	free((void *)cwd);
	return 0;
}

