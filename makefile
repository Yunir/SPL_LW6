FLAGS=-ggdb -c -o

all: main

main: output/main.o output/mem.o
	gcc -ggdb -o main output/main.o output/mem.o


output/main.o: main.c
	gcc $(FLAGS) output/main.o main.c

output/mem.o: mem.c
	gcc $(FLAGS) output/mem.o mem.c

clean:
	rm -f main *.o

shared:
	gcc -fPIC -c mem.c
	gcc -shared -o mf.so -fPIC mem.o
