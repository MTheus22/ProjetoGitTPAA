LDFLAGS = -lssl -lcrypto

all: run clean

run: compile
	-./git_sim.o

compile:
	gcc -o git_sim.o ./src/*.c $(LDFLAGS)

all_debug: run_debugger clean

run_debugger: compile_debug
	gdb git_sim.o

compile_debug:
	gcc -o git_sim.o ./src/*.c $(LDFLAGS) -g

clean:
	rm *.o
