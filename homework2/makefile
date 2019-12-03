.PHONY: clean

all: clean dirs ut_all

ut_all: src/main.cpp src/circular_sector.h src/ellipse.h src/triangle.h test/ut_sort.h
	g++ -std=c++11 src/main.cpp -o bin/ut_all -lgtest -lpthread -Wfatal-errors

dirs:
	mkdir -p bin

clean:
	rm -f bin/*
