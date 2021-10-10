all: dice
	@cp dice $(PROROOT)/build/bin/dice

dice: dice.c
	$(CC) -o dice dice.c

clean:
	@rm -r dice

.PHONY: all clean