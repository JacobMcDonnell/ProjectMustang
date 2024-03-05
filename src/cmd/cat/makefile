CFLAGS=-Wall -Werror

build: cat
	@cp cat $(PROROOT)/build/bin/cat

cat: cat.c
	$(CC) $(CFLAGS) -o cat cat.c

clean:
	@rm -r cat

.PHONY: build clean
