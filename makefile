all: compile run clean

run:
	./program.o

compile:
	gcc -o program.o branch.c main.c

clean:
	rm *.o
