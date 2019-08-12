test: chess.o gameb.o samplemain.o
	g++ -o test *.o

samplemain.o: samplemain.cc chess.h
	g++ -c samplemain.cc

chess.o: game.h board_node.h
	g++ -c chess.cc

gameb.o: game.h
	g++ -c gameb.cc

clean:
	rm *.o
