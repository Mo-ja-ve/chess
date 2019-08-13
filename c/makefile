CC = g++ -time

MAKE_EXE = -o



all: exe

exe: main.o chess_types.o
	$(CC) main.o chess_types.o $(MAKE_EXE) exe

main.o: main.cc
	g++ -c main.cc

chess_types.o: chess_types.h chess_types.cc
	g++ -c chess_types.cc
