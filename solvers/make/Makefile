# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -ggdb3   	adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -pedantic	turns off more extensions and generates more warnings	

CFLAGS  = -ggdb3 -std=c++17 -pedantic -Wall

MESHS = -I ../../mesh/Point \
		-I ../../mesh/LabeledPoint \
		-I ../../mesh/Face \
		-I ../../mesh/Cell \
		-I ../../mesh/Mesh

LIBS =	-I ../../lib/List \
		-I ../../lib/DynamicList \
		-I ../../lib/Vector \
		-I ../../lib/Matrix
		
FVCS =	-I ../../fvc/Boundary \
		-I ../../fvc/interpolate \
		-I ../../fvc/d \
		-I ../../fvc/Field

srcs_cavity = $(wildcard ../cavity/*.cpp)  


objs = cavity.o Point.o Face.o Cell.o Mesh.o List.o Vector.o Matrix.o Boundary.o interpolate.o d.o CellField.o FaceField.o CellGradField.o FaceGradField.o DynamicList.o

cavity: pre-build $(objs) 
	$(CC) $(CFLAGS) $(objs) -o cavity

pre-build:
	ln -sf ../../lib/make/*.o .
	ln -sf ../../mesh/make/*.o .
	ln -sf ../../fvc/make/*.o .
	
cavity.o:	$(srcs_cavity)
	$(CC) $(CFLAGS) $(LIBS) $(MESHS) $(FVCS) -c $<

clean: 
	rm -f *.o cavity
