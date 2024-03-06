#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include "builtin.h"

size_t getargs(const size_t n, char *args[n], FILE * const stream);
int shellexec(size_t n, char * const args[n]);
/* int shellredirect(size_t n, char * const args[n], const char * const file, const int mode); */
/* int shelltofile(size_t n, char * const args[n], const int fd); */

static bool run = true;
static const char * const delim = "\t\n &|><";

int main(int argc, char *argv[]) {
	char *words[BUFSIZ] = {NULL};
	FILE *fp = stdin;
	size_t numberofwords = 0;
	if (argc == 2) {
		if ((fp = fopen(argv[1], "r")) == NULL) {
			perror("jsh");
			return EXIT_FAILURE;
		}
	}
	while (run) {
		printf("$ ");
		numberofwords = getargs(BUFSIZ, words, fp);
		shellexec(numberofwords, words);
		for (int i = 0; i < numberofwords; i++) {
			free(words[i]);
			words[i] = NULL;
		}
	}
	return 0;
}

size_t getargs(const size_t n, char *args[n], FILE * const stream) {
	char *line = (char *)malloc(BUFSIZ), *tofree, *token;
	size_t linecap = 0, num = 0;
	getline(&line, &linecap, stream);
	tofree = line;
	while ((token = strsep(&line, delim)) != NULL) {
		if (strcmp(token, "") != 0) {
			args[num++] = strdup(token);
		}
	}
	free((void *)tofree);
	return num;
}

int shellexec(const size_t n, char * const args[n]) {
	int index;
	if (strcmp(args[0], "exit") == 0) {
		run = false;
		return EXIT_SUCCESS;
	} else if ((index = checkbuiltin(args[0])) != -1) {
		return execbuiltin(index, n, args);
	}
	pid_t pid = fork();
	int status;
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("jsh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("jsh");
		exit(EXIT_FAILURE);
	} else {
		do {
		  waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return EXIT_SUCCESS;
}


/* int shellredirect(size_t n, char * const args[n], const char * const file, const int mode) { */
/* 	int fd = open(file, mode); */
/* 	int status; */
/* 	if (mode & O_WRONLY || mode & O_APPEND) { */
/* 		status = shelltofile(n, args, fd); */
/* 	} else if (mode & O_RDONLY) { */
/* 		status = EXIT_FAILURE; */
/* 	} else { */
/* 		status = EXIT_FAILURE; */
/* 	} */
/* 	close(fd); */
/* 	return status; */
/* } */

/* int shelltofile(size_t n, char * const args[n], const int fd) { */
/* 	pid_t pid = fork(); */
/* 	int status; */
/* 	if (pid == 0) { */
/* 		close(STDOUT_FILENO); */
/* 		dup2(fd, STDOUT_FILENO); */
/* 		if (execvp(args[0], args) == -1) { */
/* 			perror("jsh"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		exit(EXIT_SUCCESS); */
/* 	} else if (pid < 0) { */
/* 		perror("jsh"); */
/* 		exit(EXIT_FAILURE); */
/* 	} else { */
/* 		do { */
/* 		  waitpid(pid, &status, WUNTRACED); */
/* 		} while (!WIFEXITED(status) && !WIFSIGNALED(status)); */
/* 	} */
/* 	return EXIT_SUCCESS; */
/* } */
