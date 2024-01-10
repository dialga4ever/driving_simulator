CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

all: library/textureUtility.o car 
	$(CC) main.cpp library/car.o library/textureUtility.o $(LDFLAGS) $(OPTS) -o main

menu: menu.cpp library/textureUtility.o
	$(CC) $< library/textureUtility.o $(LDFLAGS) $(OPTS) -o $@

car: library/car.o

lib: library/textureUtility.o library/car.o

library/textureUtility.o: library/textureUtility.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/car.o: library/car.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

clean:
	rm main
