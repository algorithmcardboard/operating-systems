CC=g++
CFLAGS=-I
BINDIR=../bin

compile: init.cpp cpu.o event.o process.o processtable.o prio.o fcfs.o lcfs.o roundrobin.o sjf.o
	$(CC) -o $(BINDIR)/scheduler init.cpp $(BINDIR)/cpu.o $(BINDIR)/event.o $(BINDIR)/process.o $(BINDIR)/processtable.o $(BINDIR)/prio.o $(BINDIR)/fcfs.o $(BINDIR)/lcfs.o $(BINDIR)/roundrobin.o $(BINDIR)/sjf.o

prio.o: scheduler/priority.cpp abs_scheduler.o
	g++ -c scheduler/priority.cpp -o $(BINDIR)/prio.o

fcfs.o: scheduler/fcfs.cpp abs_scheduler.o
	g++ -c scheduler/fcfs.cpp -o $(BINDIR)/fcfs.o

lcfs.o: scheduler/lcfs.cpp abs_scheduler.o
	g++ -c scheduler/lcfs.cpp -o $(BINDIR)/lcfs.o

roundrobin.o: scheduler/round_robin.cpp abs_scheduler.o
	g++ -c scheduler/round_robin.cpp -o $(BINDIR)/roundrobin.o

sjf.o: scheduler/sjf.cpp abs_scheduler.o
	g++ -c scheduler/sjf.cpp -o $(BINDIR)/sjf.o

abs_scheduler.o: scheduler/abstract_scheduler.h
	g++ -c scheduler/abstract_scheduler.h -o $(BINDIR)/abs_scheduler.o

cpu.o: cpu.cpp cpu.h ds/processstate.h
	$(CC) -c cpu.cpp -o $(BINDIR)/cpu.o

processstate.o: ds/processstate.h
	$(CC) -c ds/processstate.h -o $(BINDIR)/processstate.o

event.o: ds/event.cpp ds/event.h ds/processstate.h ds/processstate.h
	$(CC) -c ds/event.cpp  -o $(BINDIR)/event.o

process.o: ds/process.cpp ds/process.h ds/processstate.h processstate.o
	$(CC) -c ds/process.cpp -o $(BINDIR)/process.o

processtable.o: ds/processtable.cpp ds/processtable.h process.o processstate.o
	$(CC) -c ds/processtable.cpp -o $(BINDIR)/processtable.o



setup:
	mkdir ../bin


.PHONY : clean
clean:
	-rm bin/scheduler bin/*.o
