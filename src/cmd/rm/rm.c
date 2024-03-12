#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <err.h>
#include <string.h>
#include <stdlib.h>

int rm(char *);
int removedir(const char * const);

bool rflag = false,
	 iflag = false,
	 fflag = false;

int main(int argc, char *argv[]) {
	char arg = 0;
	while ((arg = getopt(argc, argv, "Rrfi")) != -1) {
		switch (arg) {
			case 'r':
			case 'R':
				rflag = true;
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
				printf("usage: rm [-f | -i] [-r] file ...\n");
				break;
		}
	}
	while (--argc > 0) {
		if ((*++argv)[0] != '-') {
			rm(*argv);
		}
	}
	return 0;
}

int rm(char *path) {
	char c = 0;
	if (iflag) {
		fprintf(stderr, "remove %s? [y/N] ", path);
		c = getchar();
		if (c != 'Y' && c != 'y') {
			return -1;
		}
	}
	struct stat sbuf;
	if (lstat(path, &sbuf) != 0 && !fflag) {
		perror("rm");
		return -1;
	}
	if (!fflag) {
		uid_t uid = getuid();
		if (sbuf.st_uid != uid) {
			fprintf(stderr, "remove %s? [y/N] ", path);
			c = getchar();
			if (c != 'Y' && c != 'y') {
				return -1;
			}
		}
	}
	if (S_ISDIR(sbuf.st_mode) && rflag) {
		if (removedir(path) != 0) {
			return -1;
		}
		if (rmdir(path) != 0) {
			perror("rm");
			return -1;
		}
	} else if (S_ISDIR(sbuf.st_mode)) {
		warnc(EISDIR, "%s", path);
		return -1;
	} else {
		if (unlink(path) != 0) {
			perror("rm");
		}
	}
	return 0;
}

int removedir(const char * const path) {
	DIR *dir;
	int status = 0;
	if ((dir = opendir(path)) == NULL) {
		perror("rm");
		return -1;
	}
	struct dirent *entry = NULL;
	while ((entry = readdir(dir)) != NULL) {
		char *name = entry->d_name;
		if (strcmp(name, ".") != 0 && strcmp(name, "..") != 0) {
			size_t len = strlen(path) + strlen(name) + 3;
			char *newpath = (char *)malloc(len);
			if (newpath == NULL) {
				exit(EXIT_FAILURE);
			}
			strncat(newpath, path, len);
			strncat(newpath, "/", (len -= strlen(path)));
			strncat(newpath, name, --len);
			status = rm(newpath);
			free((void *)newpath);
		}
		if (status != 0) {
			break;
		}
	}
	if (closedir(dir) != 0) {
		perror("rm");
		return -1;
	}
	return status;
}

