# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -ggdb3   	adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -pedantic	turns off more extensions and generates more warnings	

CFLAGS  = -ggdb3 -std=c++17 -pedantic -Wall

INCS = -I ../Boundary \
	   -I ../Field \
	   -I ../interpolate \
	   -I ../d

UTILS = -I ../../mesh/Point \
		-I ../../mesh/LabeledPoint \
		-I ../../mesh/Face \
		-I ../../mesh/Cell \
		-I ../../mesh/Mesh

LIBS =	-I ../../lib/List \
		-I ../../lib/DynamicList \
		-I ../../lib/Vector \
		-I ../../lib/Matrix
		
srcs_Boundary = $(wildcard ../Boundary/*.cpp) 
srcs_interpolate = $(wildcard ../interpolate/*cpp)
srcs_d = $(wildcard ../d/*cpp)
srcs_CellField = $(wildcard ../Field/CellField.cpp)
srcs_FaceField = $(wildcard ../Field/FaceField.cpp)
srcs_CellGradField = $(wildcard ../Field/CellGradField.cpp)
srcs_FaceGradField = $(wildcard ../Field/FaceGradField.cpp)

objs = Boundary.o interpolate.o d.o CellField.o FaceField.o CellGradField.o FaceGradField.o

all: pre-build $(objs) 

pre-build:
	ln -sf ../../lib/make/*.o .
	ln -sf ../../mesh/make/*.o .
	
Boundary.o:	$(srcs_Boundary)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

interpolate.o: $(srcs_interpolate)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

CellField.o: $(srcs_CellField)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

FaceField.o: $(srcs_FaceField)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

CellGradField.o: $(srcs_CellGradField)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

FaceGradField.o: $(srcs_FaceGradField)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

d.o: $(srcs_d)
	$(CC) $(CFLAGS) $(INCS) $(UTILS) $(LIBS) -c $<

clean: 
	rm -f *.o 
