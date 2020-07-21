
all: clean tools

clean:
	rm -rf bin
	mkdir -p bin

thoth:
	#g++ -std=c++11 -c src/trie.cpp -lm -o bin/trie.o
	g++ -std=c++11 -c src/language.cpp -lm -o bin/language.o
	g++ -std=c++11 -c src/rand.cpp -o bin/rand.o
	g++ -std=c++11 -c src/thoth.cpp -o bin/thoth.o
	ld -relocatable bin/language.o bin/thoth.o bin/rand.o -o bin/thoth.so

wasm:
	rm -rf wasm
	mkdir -p wasm
	emcc -std=c++11 -Isrc tools/helloworld-wasm.cpp \
		src/thoth.cpp src/language.cpp src/rand.cpp -o wasm/thoth.js \
		-s 'EXTRA_EXPORTED_RUNTIME_METHODS=["ccall","cwrap"]' \
		-s EXPORTED_FUNCTIONS="['_main','_get_word','_generate']"

android:
	# export NDK_PROJECT_PATH="$(pwd)/tools"
	rm -rf tools/libs tools/obj
	~/Android/android-ndk-r21/ndk-build APP_STL=c++_static

tools: test cli

test: thoth
	g++ -std=c++11 -c tools/test.cpp -o bin/test.o
	g++ bin/test.o bin/thoth.so -o bin/test

cli: thoth
	g++ -std=c++11 -c tools/cli.cpp -o bin/cli.o
	g++ bin/cli.o bin/thoth.so -o bin/thoth
