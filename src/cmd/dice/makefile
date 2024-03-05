CFLAGS=-Wall -Werror

build: dice
	@cp dice $(PROROOT)/build/bin/dice

dice: dice.c
	$(CC) $(CFLAGS) -o dice dice.c

clean:
	@rm -r dice

.PHONY: build clean
