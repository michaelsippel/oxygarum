SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

INCLUDE = -I/usr/include/ -I../include
LIBDIR  = -L/usr/X11R6/lib 

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LDFLAGS = 
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lpng
SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

all: $(OBJS) lib

%.c : %.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)  

lib: $(OBJS)
	ar -rcs cliter.a $^

clean:
	rm $(OBJS)

