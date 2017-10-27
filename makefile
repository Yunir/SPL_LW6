FLAGS=-ggdb -c -o

all: main

main: main.o mem.o
	gcc -ggdb -o main main.o mem.o

mem.o: mem.c
	gcc $(FLAGS) mem.o mem.c
clean:
	rm -f main *.o
