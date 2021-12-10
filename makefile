chess: ChessMain.o classes.o ChessBoard.o Game.o 
	g++ -g ChessMain.o classes.o ChessBoard.o Game.o -o chess

ChessMain.o: ChessMain.cpp classes.h
	g++ -Wall -g -c ChessMain.cpp

classes.o: classes.cpp classes.h
	g++ -Wall -g -c classes.cpp

ChessBoard.o: ChessBoard.cpp classes.h
	g++ -Wall -g -c ChessBoard.cpp

Game.o: Game.cpp classes.h
	g++ -Wall -g -c Game.cpp

clean:
	rm -f *.0 chess
