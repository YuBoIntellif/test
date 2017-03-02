.PHONY:all
all:libJNIFind.so

JNIFind.class:JNIFind.java
	javac JNIFind.java

JNIFind.h:JNIFind.class
	javah JNIFind

libJNIFind.so:JNIFind.cpp JNIFind.h
	g++ -I/usr/lib/jvm/java-8-oracle/include/linux/ -I/usr/lib/jvm/java-8-oracle/include/ -fPIC -shared -o $@ JNIFind.cpp
