.PHONY:all
all:libfind.so install

libfind.so:find.cpp find.hpp
	g++ -O3 -fPIC -shared -o $@ $^ -lm -lrt -ltbb -msse -mavx

.PHONY:install
install:
	sudo install libfind.so /usr/lib
	sudo install find.hpp /usr/include

.PHONY:clean
clean:
	rm -f *.so
