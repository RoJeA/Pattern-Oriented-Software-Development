.PHONY:clean gtest mkdir wx
BIN=bin
SRC=src
TEST=test
CC=g++
CFLAG=-std=c++11 -Wfatal-errors

all:clean mkdir $(BIN)/hw8 obj/text_frame.o #bin/ut_all
# bin/ut_all: $(TEST)/ut_main.cpp obj/find_visitor.o obj/update_path_visitor.o obj/filesystem_builder.o $(SRC)/null_iterator.h  $(SRC)/visitor.h $(SRC)/link.h $(SRC)/file.h  $(SRC)/folder.h  $(SRC)/node.h $(TEST)/ut_fs.h
# 	g++ -std=c++11 -Wfatal-errors -o $@ $< -lgtest -lpthread
# obj/find_visitor.o: $(SRC)/find_visitor.cpp $(SRC)/find_visitor.h
# 	$(CC) $(CFLAG) -c $< -o $@
# obj/update_path_visitor.o: $(SRC)/update_path_visitor.cpp $(SRC)/update_path_visitor.h
# 	$(CC) $(CFLAG) -c $< -o $@
# obj/filesystem_builder.o: $(SRC)/filesystem_builder.cpp $(SRC)/filesystem_builder.h
# 	$(CC) $(CFLAG) -c $< -o $@
# gtest:
# 	$(BIN)/ut_all
#wxWidgets
obj/text_frame.o: $(SRC)/text_frame.cpp $(SRC)/text_frame.h $(SRC)/tree_frame.h
	$(CC) $(CFLAG) -c $< `wx-config --cxxflags` -o $@ -lgtest -lpthread

$(BIN)/hw8: $(SRC)/tree_test.cpp $(SRC)/tree_test.h $(SRC)/tree_frame.h
	$(CC) $(CFLAG) $< `wx-config --libs` `wx-config --cxxflags` -o $@ -lgtest -lpthread
wx:
	$(BIN)/hw8 wxtest
#wxWidgetsEnd
clean:
	rm -f $(BIN)/* obj/*
mkdir:
	mkdir -p $(BIN)
