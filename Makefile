CC = clang
all: Makefile encrypt

encrypt: Makefile encrypt.c
	$(CC) $(CFLAGS) encrypt.c -o encrypt

clean:
	rm -f encrypt
