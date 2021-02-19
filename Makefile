INCS=-I.
CCOPTS=-O3
#CCOPTS=-glldb

candyland: candyland.o deck.o board.o
	g++ $(CCOPTS) -o candyland candyland.o deck.o board.o

candyland.o: candyland.h candyland.cc common.h
	g++ -c $(CCOPTS) $(INCS) -o candyland.o candyland.cc

deck.o: deck.h deck.cc common.h
	g++ -c $(CCOPTS) $(INCS) -o deck.o deck.cc

board.o: board.h board.cc common.h
	g++ -c $(CCOPTS) $(INCS) -o board.o board.cc

clean:
	rm -f *.o candyland
