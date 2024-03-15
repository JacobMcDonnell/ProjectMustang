/* TODO:
 * - add flags
 * - add option to print more file information
 */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

void dirwalk(DIR *);
void error(char *);
void printdirent(struct dirent *);
void printfile(char *);

/* print information about files and directories */
int main(int argc, char **argv)
{
	DIR *dp;
	if (argc == 1) {
		if ((dp = opendir(".")) == NULL) {
			perror("ls");
			return -1;
		}
		dirwalk(dp);
		closedir(dp);
	} else {
		while (--argc > 0 && !ferror(stdout)) {
			errno = 0;
			if ((dp = opendir(*++argv)) == NULL) {
				perror("ls");
				continue;
			}
			dirwalk(dp);
			closedir(dp);
		}
	}
}

/* dirwalk: read all the directory entries in a directory */
void dirwalk(DIR *d)
{
	struct dirent *dir;
	while ((dir = readdir(d)) != NULL) {
		errno = 0;
		if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
			continue;
		printdirent(dir);
	}
	if (errno != 0) {
		perror("ls");
	}
	free((void *)dir);
}

/* printdirent: print a directory entry and any selected information */
void printdirent(struct dirent *dir)
{
	printf("%s\n", dir->d_name);
}

/* printfile: print a file and any other selected information */
void printfile(char *name)
{
	struct stat stbuf;
	int e = stat(name, &stbuf);
	if (e != 0) {
		perror("ls");
		return;
	}
	printf("%s\n", name);
}

