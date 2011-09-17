CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


all: ArpaLmReader.o
    $(CC) $(LFLAGS) $(OBJS) -o berkeleylm 

ArpaLmReader.o: ArpaLmReader.cpp
    $(CC) $(CFLAGS) ArpaLmReader.cpp
