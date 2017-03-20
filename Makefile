INCDIR = ../include
LIBDIR = ../lib

INC = -I $(INCDIR)
LIB = -L $(LIBDIR)

CC = gcc
CFLAGS  = -Wall
TARGET = tsclib_test

all: $(TARGET)

$(TARGET): $(TARGET).c $(TARGET).h
	$(CC) $(TARGET).c $(CFLAGS) $(INC) $(LIB) -o $(TARGET) -ltsc

clean:
	$(RM) $(TARGET)