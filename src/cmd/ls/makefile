CFLAGS=-Wall -Werror

build: ls
	@cp ls $(PROROOT)/build/bin/ls

ls: ls.c
	$(CC) $(CFLAGS) -o ls ls.c

clean:
	@rm -r ls

.PHONY: build clean
