all: main

main: main.o bmp_func.o
	gcc -ggdb -o main main.o bmp_func.o

clean:
	rm -f main
