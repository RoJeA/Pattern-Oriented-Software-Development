.PHONY: dirs clean

all: clean regex
regex:
	g++ ./src/regex.cpp -o ./bin/regex.o -lgtest -lpthread

dirs:
	mkdir -v -p ./bin

clean:$(BIN)
	rm -rf $^
