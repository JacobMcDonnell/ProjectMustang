#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>

void fileoutput(FILE *, const char *);
bool isdir(const char *);

/* concatinate files to a file stream */
int main(int argc, char **argv)
{
	FILE *fp;
	if (argc == 1) {
		fileoutput(stdin, "stdin");
	} else {
		while (--argc > 0 && !ferror(stdout)) {
			if (isdir(*++argv)) {
				perror("cat");
				continue;
			}
			if ((fp = fopen(*argv, "r")) == NULL) {
				perror("cat");
				continue;
			}
			fileoutput(fp, *argv);
		}
	}
	if (ferror(stdout)) {
		perror("cat");
		return -1;
	}
	return 0;
}

/* fileoutput: output a file to stdout */
void fileoutput(FILE *fp, const char *name)
{
	int c;
	while ((c = getc(fp)) != EOF)
		putc(c, stdout);
	if (ferror(fp)) {
		perror("cat");
	}
	fclose(fp);
}

/* isdir: return true if the file as the path is a directory */
bool isdir(const char *path)
{
	struct stat sbuf;
	stat(path, &sbuf);
	return S_ISDIR(sbuf.st_mode);
}

