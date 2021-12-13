OBJS	= Bishop.o ChessBoard.o ChessMain.o Functions.o Game.o King.o Knight.o Pawn.o Piece.o Queen.o Rook.o
SOURCE	= Bishop.cpp ChessBoard.cpp ChessMain.cpp Functions.cpp Game.cpp King.cpp Knight.cpp Pawn.cpp Piece.cpp Queen.cpp Rook.cpp
HEADER	= Bishop.h ChessBoard.h Functions.h Game.h King.h Knight.h Pawn.h Piece.h Queen.h Rook.h
OUT	= chess
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

chess: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Bishop.o: Bishop.cpp
	$(CC) $(FLAGS) Bishop.cpp 

ChessBoard.o: ChessBoard.cpp
	$(CC) $(FLAGS) ChessBoard.cpp 

ChessMain.o: ChessMain.cpp
	$(CC) $(FLAGS) ChessMain.cpp 

Functions.o: Functions.cpp
	$(CC) $(FLAGS) Functions.cpp 

Game.o: Game.cpp
	$(CC) $(FLAGS) Game.cpp 

King.o: King.cpp
	$(CC) $(FLAGS) King.cpp 

Knight.o: Knight.cpp
	$(CC) $(FLAGS) Knight.cpp 

Pawn.o: Pawn.cpp
	$(CC) $(FLAGS) Pawn.cpp 

Piece.o: Piece.cpp
	$(CC) $(FLAGS) Piece.cpp 

Queen.o: Queen.cpp
	$(CC) $(FLAGS) Queen.cpp 

Rook.o: Rook.cpp
	$(CC) $(FLAGS) Rook.cpp 


clean:
	rm -f $(OBJS) $(OUT)
