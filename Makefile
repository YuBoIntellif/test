.PHONY:all
all:
	make -C src
	make -C test
	make -C jni

.PHONY:clean
clean:
	make -C src clean
	make -C test clean
	make -C jni clean

.PHONY:install
install:
	make -C src install

.PHONY:test
test:
	make -C test test
	make -C jni test
