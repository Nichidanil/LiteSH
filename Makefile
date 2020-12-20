all: bin/lab6


bin/lab6: build/main.o build/LiteSH.o
	g++ -Wall -g build/main.o build/LiteSH.o -I./home/danil/3course/OC/lab6/lib/libm.so -ldl -o bin/lab6

build/main.o: src/main.cpp
	g++ -Wall -c -g src/main.cpp -o  build/main.o

build/LiteSH.o: src/LiteSH.cpp
	g++ -Wall -c -g src/LiteSH.cpp -o build/LiteSH.o


clean:
	rm -rf build/*.o bin/lab6
