CXX = g++
CXXFLAGS = -O3 -Wall
AR = ar
ARFLAGS = rv
OBJECTS = basiccube3.o cube3.o position.o solution.o
LIB = libsarumawashi.a

$(LIB): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJECTS)

#install:
#	cp *.h ../include/
#	cp $(LIB) ../lib/

clean:
	rm -f *.o *.a
