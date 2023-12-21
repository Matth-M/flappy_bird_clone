COMPILER=g++
CFLAGS=-Wall -g -Wextra
SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))
LINKER_FLAGS=SDL2
EXEC=main

.PHONY: all 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(COMPILER) $^ -l$(LINKER_FLAGS) -o $@ 

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $^ -o $@

.PHONY: clean 
clean:
	rm -f  $(EXEC) 
	rm -f *.o

.PHONY:run
run: all
	./$(EXEC)
