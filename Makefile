INCDIR = ../include
LIBDIR = ../lib

CC = gcc

INC = -I $(INCDIR)
LIB = -L $(LIBDIR)

PROGRAM = tsctest
OBJS = tsclib_rw.o tsclib_test.o
HDRS = tsclib_test.h

all: $(PROGRAM)

tsclib_rw.o: tsclib_rw.c $(HDRS)
	$(CC) $(FLAGS) $(INC) $(LIB) -ltsc -c tsclib_rw.c

tsclib_test.o: tsclib_test.c $(HDRS)
	$(CC) $(FLAGS) $(INC) -c tsclib_test.c

$(PROGRAM): $(OBJS) $(LIBDIR)/libtsc.a
	$(CC) $(LIB) -o $(PROGRAM) $(OBJS) -ltsc

clean:
	$(RM) $(OBJS) $(TARGET)