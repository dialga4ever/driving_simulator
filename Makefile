CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

all: library/textureUtility.o car library/levelLoader.o library/settings.o library/choixLevel.o library/menu.o
	$(CC) main.cpp  library/car.o library/textureUtility.o library/levelLoader.o library/settings.o library/choixLevel.o library/menu.o $(LDFLAGS) $(OPTS) -o main

car: library/car.o  

settings: library/settings.o

levelLoader: library/levelLoader.o

choixLevel: library/choixLevel.o

menu: library/menu.o

lib: library/textureUtility.o library/car.o library/levelLoader.o library/settings.o library/choixLevel.o library/settings.o library/menu.o

library/textureUtility.o: library/textureUtility.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/car.o: library/car.cpp library/settings.o
	$(CC) -c $< library/settings.o $(LDFLAGS) $(OPTS) -o $@

library/levelLoader.o: library/levelLoader.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/choixLevel.o: library/choixLevel.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/menu.o: library/menu.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/settings.o:	library/settings.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@
clean:
	rm main
