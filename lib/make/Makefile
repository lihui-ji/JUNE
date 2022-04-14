# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -ggdb3   	adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -pedantic	turns off more extensions and generates more warnings	

CFLAGS  = -ggdb3 -std=c++17 -pedantic -Wall

INCS = 	-I ../List \
		-I ../Vector \
		-I ../DynamicList \
		-I ../Matrix

srcs_List = $(wildcard ../List/*.cpp)
srcs_Vector = $(wildcard ../Vector/*.cpp)
srcs_DynamicList = $(wildcard ../DynamicList/*.cpp)
srcs_Matrix = $(wildcard ../Matrix/*.cpp)

all: List.o Vector.o DynamicList.o Matrix.o

List.o: $(srcs_List) 
	$(CC) $(CFLAGS) $(INCS) -c $<	

Vector.o: $(srcs_Vector) 
	$(CC) $(CFLAGS) $(INCS) -c $<	

DynamicList.o: $(srcs_DynamicList) 
	$(CC) $(CFLAGS) $(INCS) -c $<	

Matrix.o: $(srcs_Matrix) 
	$(CC) $(CFLAGS) $(INCS) -c $<	

clean: 
	rm -f *.o 