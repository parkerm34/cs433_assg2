#
#	Makefile for OpenGL example from Chapter 1 in Red Book
#

CC = g++ 
CFLAGS = -D_DEBUG
CPPFLAGS = -g

.cpp.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@  $<

LIBS = -framework OpenGL -framework GLUT -lglew -lm 

SRCS = assg2.cpp LoadShaders.cpp
OBJS = assg2.o LoadShaders.o 

example1: $(OBJS) LoadShaders.h
	g++ -g -o assg2 $(OBJS) $(LIBS)

clean:
	rm -f assg2 *.o
