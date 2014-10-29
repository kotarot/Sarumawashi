CXX = g++
CXXFLAGS = -O3 -Wall -I./sarumawashi
#OBJECTS = sample.o
LDFLAGS = -O3 -Wall -L./sarumawashi -lsarumawashi
TARGETS = sample size solve

all: $(TARGETS)

sample: sample.o
	$(CXX) -o sample sample.o $(LDFLAGS)

size: size.o
	$(CXX) -o size size.o $(LDFLAGS)

solve: solve.o
	$(CXX) -o solve solve.o $(LDFLAGS)

clean:
	rm -f *.o $(TARGETS)

