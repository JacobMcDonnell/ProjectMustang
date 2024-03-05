#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

size_t getargs(const size_t n, char *args[n], FILE * const stream);
int shellexec(size_t n, char * const args[n]);

static bool run = true;

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
		shellexec(BUFSIZ, words);
		for (int i = 0; i < numberofwords; i++) {
			free(words[i]);
			words[i] = NULL;
		}
	}
	return 0;
}

size_t getargs(const size_t n, char *args[n], FILE * const stream) {
	size_t i = 0;
	char c = 0, s[BUFSIZ], *sp = s;
	memset(s, '\0', sizeof(s));
	while ((c = fgetc(stream)) != EOF && i < n && sp < s + BUFSIZ) {
		if (isspace(c)) {
			*sp = '\0';
			args[i++] = strdup(s);
			sp = s;
			if (strcmp(args[i-1], "") == 0) {
				free(args[i-1]);
				args[i-1] = NULL;
				i--;
			}
			if (c == '\n') {
				break;
			}
		} else {
			*sp++ = c;
		}
	}
	return i;
}

int shellexec(size_t n, char * const args[n]) {
	if (strcmp(args[0], "exit") == 0) {
		run = false;
		return 0;
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
	return 0;
}

