all:
	make -C src
#	make -C converters
	make -C demo

clean:
	make -C src clean
#	make -C converters clean
	make -C demo clean

