CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

all:
	$(CC) main.cpp $(LDFLAGS) $(OPTS) -o main

menu: menu.cpp library/textureUtility.o
	$(CC) $< library/textureUtility.o $(LDFLAGS) $(OPTS) -o $@

lib: library/textureUtility.o

library/textureUtility.o: library/textureUtility.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@


clean:
	rm main
