# makefile for scheduling program
#
# make rr - for round-robin scheduling
# make fcfs - for FCFS scheduling
# make sjf - for SJF scheduling
# make priority - for priority scheduling
# make priority_rr - for priority with round robin scheduling

CC=gcc
CFLAGS=-Wall

clean:
	rm -rf *.o
	rm -rf fifo
	rm -rf scan
	rm -rf cscan

cscan: driver.o list.o CPU.o schedule_cscan.o
	$(CC) $(CFLAGS) -o cscan driver.o schedule_cscan.o list.o CPU.o

scan: driver.o list.o CPU.o schedule_scan.o
	$(CC) $(CFLAGS) -o scan driver.o schedule_scan.o list.o CPU.o

fifo: driver.o list.o CPU.o schedule_fifo.o
	$(CC) $(CFLAGS) -o fifo driver.o schedule_fifo.o list.o CPU.o


driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c


schedule_fifo.o: schedule_fifo.c
	$(CC) $(CFLAGS) -c schedule_fifo.c

schedule_scan.o: schedule_scan.c
	$(CC) $(CFLAGS) -c schedule_scan.c

schedule_cscan.o: schedule_cscan.c
	$(CC) $(CFLAGS) -c schedule_cscan.c


list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

CPU.o: CPU.c cpu.h
	$(CC) $(CFLAGS) -c CPU.c
