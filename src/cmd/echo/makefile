CFLAGS=-Wall -Werror

build: echo
	@cp echo $(PROROOT)/build/bin/echo

echo: echo.c
	$(CC) $(CFLAGS) -o echo echo.c

clean:
	@rm -r echo

.PHONY: build clean
