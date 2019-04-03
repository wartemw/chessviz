##########################################
#           Editable options             #
##########################################

# Compiler options
CC=g++
CFLAGS=-c -Wall
LDFLAGS=
ARGV= res/input.txt
EXECUTABLE_NAME=chessviz

# Folders
SRC=src
BIN=bin
OBJ=$(BIN)/obj

# Files
SOURCE_FILES=\
	main.cpp

##########################################
#    Don't touch anything below this     #
##########################################
OBJECT_FILES=$(addprefix $(OBJ)/, $(SOURCE_FILES:.cpp=.o))

build: create_directories create_executable
	@echo "Build successful!"

create_executable: create_objects
	@$(CC) $(LDFLAGS) $(OBJECT_FILES) -o $(BIN)/$(EXECUTABLE_NAME)
	@echo "Created executable."

create_objects: $(SOURCE_FILES)
	@echo "Created objects."

create_directories: 
	@mkdir -p $(OBJ)

%.cpp:
	@echo "Compiling "$@
	@$(CC) $(LDFLAGS) -c $(SRC)/$@ -o $(OBJ)/$(patsubst %.cpp,%.o,$@)

clean:
	@rm -r -f $(BIN)

run: build
	@echo ""
	@echo "-------------"
	@echo ""
	@echo "run "
	@echo "-------------"
	@echo ""
	@./$(BIN)/$(EXECUTABLE_NAME) $(ARGV)
