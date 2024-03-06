#include "builtin.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static int shellcd(const size_t n, char * const args[n]);

static const char * const builtins[] = {
	"cd"
};

static int (*functions[])(const size_t n, char * const args[n]) = {
	shellcd
};

int execbuiltin(size_t index, const size_t n, char * const args[n]) {
	return (*functions[index])(n, args);
}

size_t checkbuiltin(const char * const function) {
	size_t len = sizeof(builtins) / sizeof(builtins[0]);
	for (size_t i = 0; i < len; i++) {
		if (strcmp(builtins[i], function) == 0) {
			return i;
		}
	}
	return -1;
}

static int shellcd(const size_t n, char * const args[n]) {
	int status;
	char *home = getenv("HOME");
	if (n == 2) {
		status = chdir(args[1]);
	} else if (n == 1) {
		status = chdir(home);
	} else {
		errno = E2BIG;
		status = -1;
	}
	if (status != 0) {
		perror("cd");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

