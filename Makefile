# By Dustin Mendoza
#

CXX=gcc
CXXFLAGS = -I. -Wall

#Seperate directories
OBJ_DIR = ./obj
SRC_DIR = ./src
INC_DIR = ./include

#Define source files and objects
SOURCES = $(wildcard src/*.c)
OBJECTS = $(SOURCES:.c=.o)

#Listing Dependencies
DEPS = intel-edison-9dof-imu-i2c.h

EXES = bin/readData

#General object from source rule
obj/%.o: src/%.c
	$(CXX) -c $(CFLAGS) $< -o $@
	mv $@ obj

all: $(EXES)

bin/readData: obj/readData.o
	$(CXX) -o $@ obj/readData.o 

clean:
	rm -rf obj/*.o bin/* 
