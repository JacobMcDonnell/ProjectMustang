CFLAGS=-Wall -Werror

build: pwd
	@cp pwd $(PROROOT)/build/bin/pwd

pwd: pwd.c
	$(CC) $(CFLAGS) -o pwd pwd.c

clean:
	@rm -r pwd

.PHONY: build clean
