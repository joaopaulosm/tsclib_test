CC = gcc
CFLAGS  = -Wall
TARGET = tsclib_test

all: $(TARGET)

$(TARGET): $(TARGET).c $(TARGET).h
	$(CC) $(TARGET).c $(CFLAGS) -o $(TARGET) 

clean:
	$(RM) $(TARGET)