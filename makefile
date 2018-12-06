all: sharedmem.o
	gcc sharedmem.o
sharedmem.o: sharedmem.c
	gcc -c sharedmem.c
run:
	./a.out