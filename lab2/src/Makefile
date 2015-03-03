CC=g++
CFLAGS=-I
BINDIR=bin

compile: init.cpp cpu.o event.o process.o processtable.o
	$(CC) -o $(BINDIR)/scheduler init.cpp $(BINDIR)/cpu.o $(BINDIR)/event.o $(BINDIR)/process.o $(BINDIR)/processtable.o

cpu.o: cpu.cpp cpu.h
	$(CC) -c cpu.cpp -o $(BINDIR)/cpu.o

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
	-rm bin/scheduler bin/*.o
