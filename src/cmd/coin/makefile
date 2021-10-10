all: coin
	@cp coin $(PROROOT)/build/bin/coin

coin: coin.c
	$(CC) -o coin coin.c

clean:
	@rm -r coin

.PHONY: all clean