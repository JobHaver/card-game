CC = g++
FLAGS = -std=c++14 -Wall -g

all : cardGame

cardGame: main.cpp
	$(CC) $(FLAGS) main.cpp -o cardGame
	
clean:
	del cardGame.exe