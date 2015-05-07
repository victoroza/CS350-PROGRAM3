COMPILER = g++
FLAGS = -std=c++0x
EXECUTABLE = program3
EXECUTABLE_GEN = program2_gen

all: prog3.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE) prog3.o
	# $(COMPILER) $(FLAGS) -o $(EXECUTABLE_GEN) program2_gen.o


prog3.o: prog3.cpp
	$(COMPILER) $(FLAGS) -c prog3.cpp

# program2_gen.o: program2_gen.cpp
# 	$(COMPILER) $(FLAGS) -c program2_gen.cpp
	
clean:
	rm -f *.o $(EXECUTABLE)