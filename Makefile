
all: clean thoth

clean:
	rm -rf bin
	mkdir -p bin

thoth:
	g++ -std=c++11 src/thoth.cpp -o bin/thoth

test: thoth
	echo "Test"

cli: thoth
	echo "CLI"
