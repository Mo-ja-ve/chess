test: chess.o gameb.o samplemain.o
	g++ -o test samplemain.o *.o

samplemain.o: samplemain.cc chess.h
	g++ -c *.cc

chess.o: game.h board_node.h
	g++ -c *.cc

gameb.o: game.h
	g++ -c *.cc

clean:
	rm *.o
