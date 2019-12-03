.PHONY:clean gtest mkdir
BIN=bin
SRC=src
TEST=test
CC=g++
CFLAG=-std=c++11 -Wfatal-errors

all:clean mkdir bin/ut_all

bin/ut_all: $(TEST)/ut_main.cpp obj/find_visitor.o obj/update_path_visitor.o $(SRC)/update_path_visitor.h $(SRC)/update_path_visitor.cpp $(SRC)/find_visitor.h  $(SRC)/find_visitor.cpp  $(SRC)/null_iterator.h  $(SRC)/visitor.h $(SRC)/link.h $(SRC)/file.h  $(SRC)/folder.h  $(SRC)/node.h $(TEST)/ut_fs.h
	g++ -std=c++11 -Wfatal-errors -o $@ $< -lgtest -lpthread

obj/find_visitor.o: src/find_visitor.cpp src/find_visitor.h
	$(CC) $(CFLAG) -c $< -o $@
obj/update_path_visitor.o: src/update_path_visitor.cpp src/update_path_visitor.h
	$(CC) $(CFLAG) -c $< -o $@
gtest:
	$(BIN)/ut_all

clean:
	rm -f $(BIN)/*

mkdir:
	mkdir -p $(BIN)
