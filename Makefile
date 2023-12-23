COMPILER=g++
CFLAGS=-Wall -g -Wextra
SRC_DIR=src
OBJ_DIR=obj
SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
LINKER_FLAGS=SDL2
EXEC=$(OBJ_DIR)/main

.PHONY: all 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(COMPILER) $^ -l$(LINKER_FLAGS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(COMPILER) $(CFLAGS) -c $^ -o $@

.PHONY: clean 
clean:
	rm -rf $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

.PHONY: run
run: all
	./$(EXEC)
