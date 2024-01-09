CC = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OPTS =  -g

all:
	$(CC) main.cpp $(LDFLAGS) $(OPTS) -o main

clean:
	rm main
