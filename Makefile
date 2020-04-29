
all: clean test

clean:
	rm -rf bin
	mkdir -p bin

thoth:
	g++ -std=c++11 -c src/thoth.cpp -lm -o bin/thoth.o
	#g++ -std=c++11 -c src/trie.cpp -o bin/trie.o

test: thoth
	g++ -std=c++11 -c tools/test.cpp -o bin/test.o
	g++ -std=c++11 bin/test.o bin/thoth.o -o bin/test
	# bin/trie.o

novel:
	g++ -std=c++11 tools/novel.cpp -o bin/novel

cli: thoth
	echo "CLI"
