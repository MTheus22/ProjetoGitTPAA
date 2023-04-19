LDFLAGS = -lssl -lcrypto

all: compile run clean

run:
	./program.o

compile:
	gcc -o program.o ./src/*.c $(LDFLAGS)

clean:
	rm *.o
