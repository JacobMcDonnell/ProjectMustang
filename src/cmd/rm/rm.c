#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

bool dflag = false,
	 iflag = false,
	 fflag = false;

int main(int argc, char *argv[]) {
	char arg = 0;
	while ((arg = getopt(argc, argv, "dfi")) != -1) {
		switch (arg) {
			case 'd':
				dflag = true;
				break;
			case 'f':
				fflag = true;
				iflag = false;
				break;
			case 'i':
				iflag = true;
				fflag = false;
				break;
			default:
				printf("usage: rm [-f | -i] [-d] file ...\n");
				break;
		}
	}
	while (--argc > 0) {
		if ((*++argv)[0] == '-') {
			continue;
		}
		if (iflag) {
			printf("remove %s? [y/N] ", *argv);
			char c = getchar();
			if (c != 'Y' && c != 'y') {
				continue;
			}
		}
		struct stat sbuf;
		if (stat(*argv, &sbuf) != 0) {
			perror("rm");
			continue;
		}
		if (S_ISDIR(sbuf.st_mode) && dflag) {
			if (rmdir(*argv) != 0) {
				perror("rm");
			}
		} else if (S_ISDIR(sbuf.st_mode)) {
				errno = EISDIR;
				char s[] = "rm: ";
				char *sp = (char *)malloc(sizeof(s) + sizeof(*argv) + 1);
				strncat(sp, s, strlen(sp) - 1);
				strncat(sp, *argv, strlen(sp));
				perror(sp);
				free((void *)sp);
				sp = NULL;
		} else {
			if (unlink(*argv) != 0) {
				perror("rm");
			}
		}
	}
	return 0;
}
