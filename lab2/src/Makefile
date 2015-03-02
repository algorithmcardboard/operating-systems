CC=g++
CFLAGS=-I
BINDIR=bin

compile: init.cpp cpu.cpp event.o process.o processtable.o
	$(CC) -o scheduler init.cpp ds/event.cpp ds/process.cpp ds/processtable.cpp

event.o: ds/event.cpp ds/event.h
	$(CC) -c ds/event.cpp -o $(BINDIR)/event.o

process.o: ds/process.cpp ds/process.h
	$(CC) -c ds/process.cpp -o $(BINDIR)/process.o

processtable.o: ds/processtable.cpp ds/processtable.h process.o
	$(CC) -c ds/processtable.cpp -o $(BINDIR)/processtable.o

setup:
	mkdir bin


.PHONY : clean
clean:
	-rm scheduler bin/*.o
