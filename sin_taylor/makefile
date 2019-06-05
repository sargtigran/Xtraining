
PROG := tsin
SOURCES := tsin.cpp
TEST_SRC := main.cpp
HEADERS := tsin.hpp
LIBS := -ltsin
OBJECTS = $(SOURCES:.cpp=.o)

BASE_PATH := .
INCLUDE_PATH = $(BASE_PATH)/include
SRC_PATH = $(BASE_PATH)/src
BIN_PATH = $(BASE_PATH)/bin
OBJ_PATH = $(BASE_PATH)/obj
LIB_PATH = $(BASE_PATH)/libs
TEST_PATH = $(BASE_PATH)/test


CC=g++

all: $(PROG)

$(PROG): $(OBJECTS)
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(LIB_PATH)
	$(CC) -shared -fPIC $(OBJ_PATH)/$(OBJECTS) -o $(LIB_PATH)/lib$(PROG).so
	$(CC) -L$(LIB_PATH) -I$(INCLUDE_PATH) $(TEST_PATH)/$(TEST_SRC) -o $(BIN_PATH)/$(PROG) $(LIBS)

%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CC) -c -fPIC $(SRC_PATH)/$(SOURCES) -I$(INCLUDE_PATH) -o $(OBJ_PATH)/$@ 
	

.PHONY: claen test
clean:
	rm -rf $(OBJ_PATH) $(BIN_PATH)


test:
	@mkdir -p test
