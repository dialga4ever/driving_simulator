CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

# List of source files
SRC_FILES = main.cpp library/car.cpp library/textureUtility.cpp library/levelLoader.cpp library/settings.cpp library/choixLevel.cpp library/menu.cpp library/collision.cpp

# List of object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) $(OPTS) -o main

# Rules for compiling individual source files
%.o: %.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

clean:
	rm -f main $(OBJ_FILES)
