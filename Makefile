OBJS = main.cpp shared.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = GameOfLife

all :
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

