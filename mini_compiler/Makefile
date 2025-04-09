CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: mini_compiler

mini_compiler: code.cpp
	$(CXX) $(CXXFLAGS) -o mini_compiler code.cpp

clean:
	rm -f mini_compiler output.asm

.PHONY: all clean 