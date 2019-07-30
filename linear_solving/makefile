
PROG := linear_solving
TARGET := liblinear_solving.so
SOURCES := linear_solving.cpp
TEST_SRC := test.cpp
HEADERS := linear_solving.hpp
OBJECTS = $(SOURCES:.cpp=.o)

BASE_PATH := .
INCLUDE_PATH = $(BASE_PATH)/include
SRC_PATH = $(BASE_PATH)/src
BIN_PATH = $(BASE_PATH)/bin
OBJ_PATH = $(BASE_PATH)/obj
LIB_PATH = $(BASE_PATH)/libs
TEST_PATH = $(BASE_PATH)/test


CC = g++ -std=c++11
DEBUG = -g
LIBS = -l$(PROG)

all: $(LIB_PATH)/$(TARGET)

$(LIB_PATH)/$(TARGET): $(OBJ_PATH)/$(OBJECTS)
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(LIB_PATH)
	$(CC) -shared $(DEBUG) -fPIC $(OBJ_PATH)/$(OBJECTS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(INCLUDE_PATH)/$(HEADERS)
	@mkdir -p $(OBJ_PATH)
	$(CC) -c $(DEBUG) -fPIC $< -I$(INCLUDE_PATH) -o $@ 
	

.PHONY: claen
clean:
	rm -rf $(OBJ_PATH) $(BIN_PATH) $(LIB_PATH)

test: $(BIN_PATH)/$(PROG)
	@cd $(TEST_PATH) && LD_LIBRARY_PATH=../$(LIB_PATH) ../$(BIN_PATH)/$(PROG)

$(BIN_PATH)/$(PROG): $(TEST_PATH)/$(TEST_SRC) $(LIB_PATH)/$(TARGET) $(INCLUDE_PATH)/$(HEADERS)
	$(CC) $(DEBUG) -L$(LIB_PATH) -I$(INCLUDE_PATH) $< -o $@ $(LIBS)
