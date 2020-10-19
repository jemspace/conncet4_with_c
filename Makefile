# -----------------------------------------------------------
#		Source code:  Makefile
#           Author:  Darya Chepurna
#     Student ID:  6152714
#    Assignment:  Program #4 connect 4
#
#	Makefile for Connect 4
#		*************
#	must be in same directory as connect4main.c gameMap.c
#		*************
#	build -compiles files connect4main.c gameMap.c sequenceChecks.c
#	clean -removes output file/ object files
#	redo -removes output and recompiles .c files
# -----------------------------------------------------------

CC = gcc
FILES = connect4main.c gameMap.c sequenceChecks.c

build: $(FILES)
	$(CC) $(FILES) -o c4.out

clean:
	rm c4.out *.o

redo: clean build