CXX=clang++-11
CXXFLAGS=-std=c++11 -O3 -g -Wall -I/usr/include/nodejs/deps/v8/include
LDFLAGS=-lv8

SRC=main.cc
OBJ=$(SRC:.cc=.o)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	rm -f main *.o

.PHONY: test
test: main
	./main
