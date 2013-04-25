SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

INCLUDE = -I/usr/include/ -I../../include
LIBDIR  = -L/usr/X11R6/lib 

CC = gcc
CFLAGS = -Wall $(INCLUDE)
OXY = ../../src/oxygarum.a

walk: $(OBJS)
	$(CC) -o $@ $^ $(LIBDIR)$(LIBRARIES) $(OXY)

%.c : %.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)  

clean:
	rm $(OBJS)

