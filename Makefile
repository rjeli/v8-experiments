#CXX=clang++-11
CXX=c++
CXXFLAGS=-std=c++11 -Wall -O2 -g -Ithirdparty/v8/include
LDFLAGS=thirdparty/v8/libv8.a -lpthread

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
