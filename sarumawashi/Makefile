CXX = g++
CXXFLAGS = -O2 -Wall
AR = ar
ARFLAGS = rv
OBJECTS = basiccube3.o cube3.o position.o
LIB = libsarumawashi.a

$(LIB): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJECTS)

#install:
#	cp *.h ../include/
#	cp $(LIB) ../lib/

clean:
	rm -f *.o *.a

