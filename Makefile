CC=g++
OPTIONS=-c -O2

all: words

words: words.o bst.o hash.o doublehash.o quadraticprobe.o linearprobe.o
	$(CC) -o words words.o bst.o hash.o doublehash.o quadraticprobe.o linearprobe.o

words.o: words.cpp bst.h hash.h doublehash.h quadraticprobe.h linearprobe.h
	$(CC) $(OPTIONS) words.cpp

bst.o: bst.cpp bst.h
	$(CC) $(OPTIONS) bst.cpp

hash.o: hash.cpp hash.h
	$(CC) $(OPTIONS) hash.cpp

doublehash.o: doublehash.cpp doublehash.h
	$(CC) $(OPTIONS) doublehash.cpp

quadraticprobe.o: quadraticprobe.cpp quadraticprobe.h
	$(CC) $(OPTIONS) quadraticprobe.cpp

linearprobe.o: linearprobe.cpp linearprobe.h
	$(CC) $(OPTIONS) linearprobe.cpp

clean:
	rm -f words words.o bst.o hash.o doublehash.o quadraticprobe.o linearprobe.o
