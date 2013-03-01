SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

INCLUDE = -I/usr/include/ -I../include
LIBDIR  = -L/usr/X11R6/lib 

CC = gcc
CFLAGS = -Wall $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lpng

all: $(OBJS) lib

%.c : %.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)  

lib: $(OBJS)
	ar -rcs oxygarum.a $^

clean:
	rm $(OBJS)
	rm oxygarum.a

