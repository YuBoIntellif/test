.PHONY:all JNIFind.so JNIFind.h libJNIFind.so Test.class
all:libJNIFind.so Test.class

JNIFind.class:JNIFind.java
	javac JNIFind.java

JNIFind.h:JNIFind.class
	javah JNIFind

libJNIFind.so:JNIFind.cpp JNIFind.h
	g++ -I/usr/lib/jvm/java-8-oracle/include/linux/ -I/usr/lib/jvm/java-8-oracle/include/ -Wl,--no-undefined -fPIC -shared -o $@ JNIFind.cpp -lfind 

Test.class:Test.java
	javac Test.java

.PHONY:test testinit test10000 test50000 test100000 test1000000
test: testinit test10000 test50000 test100000 test1000000
testinit:
	cp ../test/*.txt .

test10000:
	java -Djava.library.path='.' Test 10000 0
	java -Djava.library.path='.' Test 10000 1
	java -Djava.library.path='.' Test 10000 2
	java -Djava.library.path='.' Test 10000 3

test50000:
	java -Djava.library.path='.' Test 50000 0
	java -Djava.library.path='.' Test 50000 1
	java -Djava.library.path='.' Test 50000 2
	java -Djava.library.path='.' Test 50000 3

test100000:
	java -Djava.library.path='.' Test 100000 0
	java -Djava.library.path='.' Test 100000 1
	java -Djava.library.path='.' Test 100000 2
	java -Djava.library.path='.' Test 100000 3

test1000000:
	java -Djava.library.path='.' Test 1000000 0
	java -Djava.library.path='.' Test 1000000 1
	java -Djava.library.path='.' Test 1000000 2
	java -Djava.library.path='.' Test 1000000 3


.PHONY:clean
clean:
	rm *.so *.class *.txt
