CXX = g++
CXXFLAGS = -O3 -Wall -I./src
LDFLAGS = -O3 -Wall -L./src -lsarumawashi
TARGETS = sample size solve

all: $(TARGETS)

sample: sample.o
	$(CXX) -o sample sample.o $(LDFLAGS)

size: size.o
	$(CXX) -o size size.o $(LDFLAGS)

solve: solve.o
	$(CXX) -o solve solve.o $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(TARGETS)
