CFLAGS=-Wall -Werror

build: rm
	@cp rm $(PROROOT)/build/bin/rm

rm: rm.c
	$(CC) $(CFLAGS) -o rm rm.c

clean:
	@rm -r rm

.PHONY: build clean
