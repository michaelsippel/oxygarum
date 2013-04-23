SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

INCLUDE = -I/usr/include/ -I../../include
LIBDIR  = -L/usr/X11R6/lib 

CC = gcc
CFLAGS = -Wall $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm -lpng
CLITER = ../../src/oxygarum.a

cube: $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR)$(LIBRARIES) $(CLITER)

%.c : %.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm $(OBJS)

