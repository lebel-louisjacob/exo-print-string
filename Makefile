.PHONY: all lib clean

OUT_DIRECTORY := out
SOURCE_DIRECTORY := src

all: lib

lib: $(OUT_DIRECTORY)/lib/printCharacter.so

$(OUT_DIRECTORY)/lib/printCharacter.so: $(SOURCE_DIRECTORY)/printCharacter.cpp | $(OUT_DIRECTORY)/lib/
	g++ -shared -Wall -fPIC --std=c++23 -O3 -o $@ $^

$(OUT_DIRECTORY)/%/:
	mkdir -p $@

clean:
	rm -rf out
