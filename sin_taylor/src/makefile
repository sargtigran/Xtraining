
PROG := sinx
SOURCE := main.cpp
HEADERS :=
LIBS :=
OBJECTS = $(SOURCE:.cpp=.o)

INCLUDE_PATH := ./include



CC=g++

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROG) 

$(OBJECTS): $(SOURCE) $(HEADERS)
	$(CC) -c $(SOURCE) -I $(INCLUDE_PATH)

