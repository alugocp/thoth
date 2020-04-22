
all: clean test

clean:
	rm -rf bin
	mkdir -p bin

thoth:
	g++ -std=c++11 -c src/thoth.cpp -o bin/thoth.o

test: thoth
	g++ -std=c++11 -c tools/test.cpp -o bin/test.o
	g++ -std=c++11 bin/test.o bin/thoth.o -o bin/test

cli: thoth
	echo "CLI"
