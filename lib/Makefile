libm.so: spirit.o
	g++ -Wall -g -shared -o libm.so spirit.o

spirit.o: spirit.cpp
	g++ -c -fPIC spirit.cpp

clean:
	rm -rf *.o *.so
