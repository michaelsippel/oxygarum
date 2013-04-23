all:
	make -C src
	make -C demo/cube
	make -C demo/walk

clean:
	make -C src clean
	make -C demo/cube clean
	make -C demo/walk clean


