all: echo
	@cp echo $(PROROOT)/build/bin/echo

echo: echo.c
	$(CC) -o echo echo.c

clean:
	@rm -r echo
	
.PHONY: all clean