CC=g++ -g

OBJS=main.o MancalaBoard.o MancalaPlayer.o Human.o Computer.o Image.o

default: MancalaGame

MancalaGame: $(OBJS)
	$(CC) -o MancalaGame $(OBJS)

MancalaBoard.o: MancalaBoard.h
	$(CC) -c MancalaBoard.cpp -o MancalaBoard.o

MancalaPlayer.o: MancalaPlayer.h MancalaBoard.h
	$(CC) -c MancalaPlayer.cpp -o MancalaPlayer.o

Human.o: Human.h MancalaPlayer.h
	$(CC) -c Human.cpp -o Human.o

Computer.o: Computer.h MancalaPlayer.h
	$(CC) -c Computer.cpp -o Computer.o

Image.o: imageout.h
	$(CC) -c imageout.cpp -o Image.o

main.o: MancalaBoard.h MancalaPlayer.h Human.h Computer.h Input_Handling.h imageout.h
	$(CC) -c main.cpp -o main.o

clean:
	rm $(OBJS) MancalaGame
