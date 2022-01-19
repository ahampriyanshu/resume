all: main

main: main.o RLP.o sha3.o utils.o $(obj)
	$(CC) -o $@ $^ -lsecp256k1

main.o: main.c
	gcc -c main.c

RLP.o: RLP.c
	gcc -c RLP.c

utils.o: utils.c
	gcc -c utils.c

sha3.o: sha3.c
	gcc -c sha3.c

clean:
	rm -f *.o main