CC=g++
CFLAGS=-g -std=c++17 -Wall
EXECUTABLE=run

all: $(EXECUTABLE)

$(EXECUTABLE): BST.o event.o LLL.o main.o
	$(CC) $(CFLAGS) -o $@ $^

BST.o: BST.cpp BST.h main.h LLL.h
	$(CC) $(CFLAGS) -c $<

event.o: event.cpp event.h main.h
	$(CC) $(CFLAGS) -c $<

LLL.o: LLL.cpp LLL.h event.h main.h
	$(CC) $(CFLAGS) -c $<

main.o: main.cpp main.h event.h LLL.h BST.h error.h
	$(CC) $(CFLAGS) -c $<

clean cls:
	-rm -f $(EXECUTABLE) *.o *~ \#*		
