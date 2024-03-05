CFLAGS=-Wall -Werror

build: coin
	@cp coin $(PROROOT)/build/bin/coin

coin: coin.c
	$(CC) $(CFLAGS) -o coin coin.c

clean:
	@rm -r coin

.PHONY: build clean
