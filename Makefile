CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

all: library/textureUtility.o car library/levelLoader.o library/settings.o library/choixLevel.o library/settings.o
	$(CC) main.cpp  library/car.o library/textureUtility.o library/levelLoader.o library/settings.o library/choixLevel.o library/settings.o $(LDFLAGS) $(OPTS) -o main

menu: menu.cpp library/textureUtility.o
	$(CC) $< library/textureUtility.o $(LDFLAGS) $(OPTS) -o $@

car: library/car.o  

settings: library/settings.o

settings: library/settings.o

levelLoader: library/levelLoader.o

choixLevel: library/choixLevel.o

lib: library/textureUtility.o library/car.o library/levelLoader.o library/settings.o library/choixLevel.o library/settings.o

library/textureUtility.o: library/textureUtility.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/car.o: library/car.cpp library/settings.o library/settings.o
	$(CC) -c $< library/settings.o library/settings.o $(LDFLAGS) $(OPTS) -o $@

library/levelLoader.o: library/levelLoader.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/choixLevel.o: library/choixLevel.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@

library/settings.o:	library/settings.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@
library/settings.o:	library/settings.cpp
	$(CC) -c $< $(LDFLAGS) $(OPTS) -o $@
clean:
	rm main