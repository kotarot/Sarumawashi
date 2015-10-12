CXX = g++
CXXFLAGS = -O3 -Wall -I./src
LDFLAGS = -O3 -Wall -L./src -lsarumawashi
TARGETS = sarumawashi samplecodes

all: $(TARGETS)

sarumawashi:
	$(MAKE) -C src

samplecodes:
	$(MAKE) -C sample

.PHONY: clean
clean:
	$(MAKE) -C src clean
	$(MAKE) -C sample clean
