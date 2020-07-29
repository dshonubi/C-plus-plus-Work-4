# Makefile

# the C++ compiler
CXX     = g++

# options to pass to the compiler
CXXFLAGS = -O0 -g3 -std=c++14

All: all
all: main

main: main.cpp projectAllocation.o
	$(CXX) $(CXXFLAGS) main.cpp projectAllocation.o -o main

projectAllocation.o: projectAllocation.cpp projectAllocation.h
	$(CXX) $(CXXFLAGS) -c projectAllocation.cpp -o projectAllocation.o

deepclean: 
	rm -f *~ *.o *.gch main *.exe *.stackdump main

clean:
	-rm -f *~ *.o *.gch *.stackdump

