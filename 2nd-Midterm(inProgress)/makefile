.PHONY:clean gtest mkdir
BIN=bin
SRC=src
TEST=test
CC=g++
CFLAG=-std=c++11 -Wfatal-errors

all:clean mkdir bin/ut_all

bin/ut_all: $(TEST)/ut_midterm2.cpp $(SRC)/set.h $(SRC)/integer.h $(SRC)/element.h $(SRC)/iterator.h $(SRC)/null_iterator.h  $(SRC)/visitor.h obj/evaluate_visitor.o obj/flattened_set_visitor.o $(SRC)/flattened_set_visitor.h $(SRC)/flattened_set_visitor.cpp $(SRC)/evaluate_visitor.h  $(SRC)/evaluate_visitor.cpp
	g++ -std=c++11 -Wfatal-errors -o $@ $< -lgtest -lpthread

obj/evaluate_visitor.o: src/evaluate_visitor.cpp src/evaluate_visitor.h
	$(CC) $(CFLAG) -c $< -o $@
obj/flattened_set_visitor.o: src/flattened_set_visitor.cpp src/flattened_set_visitor.h
	$(CC) $(CFLAG) -c $< -o $@
gtest:
	$(BIN)/ut_all

clean:
	rm -f $(BIN)/*

mkdir:
	mkdir -p $(BIN)
