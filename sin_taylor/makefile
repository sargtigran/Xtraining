
PROG := sinx
SOURCES := main.cpp
HEADERS :=
LIBS :=
OBJECTS = $(SOURCES:.cpp=.o)

BASE_PATH := .
INCLUDE_PATH = $(BASE_PATH)/include
SRC_PATH = $(BASE_PATH)/src
BIN_PATH = $(BASE_PATH)/bin
OBJ_PATH = $(BASE_PATH)/obj


CC=g++

all: $(PROG)

$(PROG): $(OBJECTS)
	@mkdir -p $(BIN_PATH)
	$(CC) $(OBJ_PATH)/$(OBJECTS) -o $(BIN_PATH)/$(PROG) 

%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $(SRC_PATH)/$(SOURCES) -I $(INCLUDE_PATH) -o $(OBJ_PATH)/$@ 
	

clean:
	rm -rf $(OBJ_PATH) $(BIN_PATH)

