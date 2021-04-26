all: subfolder main

main: main.o crypto/bip39.o crypto/memzero.o crypto/hmac.o crypto/sha2.o crypto/rand.o crypto/pbkdf2.o
	$(CC) -o $@ $^

main.o: main.c
	gcc -c main.c

subfolder:
	$(MAKE) -C crypto/

clean:
	cd crypto && $(MAKE) clean
	rm -f *.o main