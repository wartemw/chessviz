##########################################
#           Editable options             #
##########################################

# Compiler options
CC=g++
LDFLAGS=-std=c++11
ARGV= res/input.txt
EXECUTABLE_NAME=chessviz

# Folders
SRC=src
TEST_DIR=test
BIN=bin
OBJ=$(BIN)/obj
#LIB_GTEST=/usr/local/lib64/libgtest.a /usr/local/lib64/libgtest_main.a -lpthread
LIB_GTEST=libs/gtest/libgtest.a libs/gtest/libgtest_main.a -lpthread

# Files
SOURCE_FILES=\
	Cell.cpp\
	Board.cpp\
	IO.cpp\

TEST_FILES=\
	Cell_test.cpp\
	Board_test.cpp\
	IO_test.cpp\

main.o:
	@$(CC) $(LDFLAGS) -c $(SRC)/main.cpp -o $(OBJ)/main.o

main_test.o:
	@$(CC) $(LDFLAGS) -c $(TEST_DIR)/main_test.cpp -o $(OBJ)/main_test.o

##########################################
#    Don't touch anything below this     #
##########################################
OBJECT_FILES=$(addprefix $(OBJ)/, $(SOURCE_FILES:.cpp=.o))

build: create_directories create_executable_main
	@echo "Build successful!"

test: create_directories create_executable_test
	@echo "Build successful!"
	@./$(BIN)/$(EXECUTABLE_NAME)_test

create_executable_main: create_objects main.o
	@$(CC) $(LDFLAGS) $(OBJECT_FILES) $(OBJ)/main.o -o $(BIN)/$(EXECUTABLE_NAME)
	@echo "Created executable."

create_executable_test: create_objects main_test.o
	@$(CC) $(LDFLAGS) $(LIB_GTEST) $(OBJECT_FILES) $(OBJ)/main_test.o -o $(BIN)/$(EXECUTABLE_NAME)_test
	@echo "Created executable."

create_objects: $(SOURCE_FILES)
	@echo "Created objects."

create_directories:
	@mkdir -p $(OBJ)

test_files:
	@$(CC) $(LDFLAGS) $(LIB_GTEST) bin/obj/main_test.o $(OBJECT_FILES) -o $(BIN)/$(EXECUTABLE_NAME)_test

%.cpp:
	@echo "Compiling "$@
	@$(CC) $(LDFLAGS) -c $(SRC)/$@ -o $(OBJ)/$(patsubst %.cpp,%.o,$@)

clean:
	@rm -r -f $(BIN)

all: build

run: build
	@echo ""
	@echo "-------------"
	@echo ""
	@echo "run "
	@echo "-------------"
	@echo ""
	@./$(BIN)/$(EXECUTABLE_NAME) $(ARGV)
