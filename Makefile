CXX = g++
CXXFLAGS = -O2 -Wall -I./sarumawashi
#OBJECTS = sample.o
LDFLAGS = -L./sarumawashi -lsarumawashi
TARGETS = sample size

all: $(TARGETS)

sample: sample.o
	$(CXX) -o sample sample.o $(LDFLAGS)

size: size.o
	$(CXX) -o size size.o $(LDFLAGS)

clean:
	rm -f *.o $(TARGETS)

