.PHONY:all
all:
	make -C src
	make -C test

.PHONY:clean
clean:
	make -C src clean
	make -C test clean

.PHONY:install
install:
	make -C src install

.PHONY:test
test:
	make -C test test
