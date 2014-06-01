SRCS = $(shell find -name '*.cpp')
HDRS = $(shell find -name '*.h')
STYLEFLAGS = --style=allman --indent-classes --indent-switches

all:
	make -C src
#	make -C converters
	make -C demo

style: $(SRCS) $(HDRS)
	astyle $(STYLEFLAGS) $^

clean:
	make -C src clean
#	make -C converters clean
	make -C demo clean

