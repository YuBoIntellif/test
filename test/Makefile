.PHONY:all
all:gen find

gen:gen.cpp base.cpp
	g++ -o $@ $^ -lm -lrt

find:find.cpp base.cpp
	g++ -O3 -o find_0 $^ -lfind -lm -lrt -ltbb -msse -mavx -DALG=0
	g++ -O3 -o find_1 $^ -lfind -lm -lrt -ltbb -msse -mavx -DALG=1
	g++ -O3 -o find_2 $^ -lfind -lm -lrt -ltbb -msse -mavx -DALG=2
	g++ -O3 -o find_3 $^ -lfind -lm -lrt -ltbb -msse -mavx -DALG=3

.PHONE:test testinit test10000 test50000 test100000 test1000000
test:testinit test10000 test50000 test100000 test1000000
testinit:
	./gen 1000   > 1000.txt
	./gen 10000  > 10000.txt
	./gen 50000  > 50000.txt
	./gen 100000 > 100000.txt
	./gen 1000000 > 1000000.txt

test10000:
	./find_0 10000
	./find_1 10000
	./find_2 10000
	./find_3 10000

test50000:
	./find_0 50000
	./find_1 50000
	./find_2 50000
	./find_3 50000

test100000:
	./find_0 100000
	./find_1 100000
	./find_2 100000
	./find_3 100000

test1000000:
	./find_0 1000000
	./find_1 1000000
	./find_2 1000000
	./find_3 1000000

.PHONE:clean
clean:
	rm -f gen find_* *.txt
