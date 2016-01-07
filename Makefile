CXX = g++

PROGRAM = calc80
 
OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
 
# implementation
 
.SUFFIXES:	.o .cpp
 
.cpp.o :
	$(CXX)  `fltk-config --cxxflags` -c -g -o 	$@ $<
 
all:	$(PROGRAM)
 

$(PROGRAM):	$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS)  `fltk-config --ldflags --use-images` -lfltk
 
clean:
	rm -f *.o $(PROGRAM)
