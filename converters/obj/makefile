SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

CFLAGS = -Wall -I../../include

convert_obj: $(OBJS)
	$(CC) -o $@ $^

%.c : %.o
	$(CC) $(CFLAGS) -o $@

clean:
	rm $(OBJS)

