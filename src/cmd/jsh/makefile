CFLAGS=-Wall -Werror

build: jsh
	@cp jsh $(PROROOT)/build/bin/jsh

jsh: jsh.c
	$(CC) $(CFLAGS) -o jsh jsh.c builtin.c

clean:
	@rm -r jsh

.PHONY: build clean
