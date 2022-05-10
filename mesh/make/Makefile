# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -ggdb3   	adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -pedantic	turns off more extensions and generates more warnings	

CFLAGS  = -ggdb3 -std=c++17 -pedantic -Wall

INCS = 	-I ../Point \
		-I ../meshMain \
		-I ../LabeledPoint \
		-I ../Face \
		-I ../Cell \
		-I ../Mesh

LIBS =	-I ../../lib/List \
		-I ../../lib/DynamicList \
		-I ../../lib/Vector \
		-I ../../lib/Matrix
		
srcs_Point = $(wildcard ../Point/*.cpp) 
srcs_LabeledPoint = $(wildcard ../LabeledPoint/*.cpp)  
srcs_Face = $(wildcard ../Face/*.cpp)
srcs_Cell = $(wildcard ../Cell/*.cpp)
srcs_Mesh = $(wildcard ../Mesh/*.cpp)

objs = Point.o LabeledPoint.o Face.o Cell.o List.o Vector.o DynamicList.o Matrix.o Mesh.o

mesh: pre-build $(objs) 

pre-build:
	ln -sf ../../lib/make/*.o .

Point.o: $(srcs_Point)
	$(CC) $(CFLAGS) $(INCS) $(LIBS) -c $<

LabeledPoint.o: $(srcs_LabeledPoint)
	$(CC) $(CFLAGS) $(INCS) $(LIBS) -c $<

Face.o: $(srcs_Face) 
	$(CC) $(CFLAGS) $(INCS) $(LIBS) -c $<

Cell.o: $(srcs_Cell) 
	$(CC) $(CFLAGS) $(INCS) $(LIBS) -c $<

Mesh.o: $(srcs_Mesh) 
	$(CC) $(CFLAGS) $(INCS) $(LIBS) -c $<	

clean: 
	rm -f *.o mesh
