COMPILER = g++
FLAGS = -std=c++0x
EXECUTABLE = program3
EXECUTABLE_GEN = program3_gen

all: prog3.o program3_gen.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) prog3.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE_GEN) program3_gen.o

prog3.o: prog3.cpp
	$(COMPILER) $(FLAGS) -c prog3.cpp

program3_gen.o: program3_gen.cpp
	$(COMPILER) $(FLAGS) -c program3_gen.cpp
	
clean:
	rm -f *.o $(EXECUTABLE)
