#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/utilities.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/node.h"

class NodeTest : public ::testing::Test{
protected:
  void SetUp() {
    hw = new Folder("test/test_folder/hw");
    a_out = new File("test/test_folder/hw/a.out");
    hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hello_txt= new File("test/test_folder/hello.txt");
    test_folder= new Folder("test/test_folder");
    TA_folder=new Folder("test/test_folder/hw/TA_folder");
    TA_folder_a_out=new File("test/test_folder/hw/TA_folder/a.out");
    test_folder->addChild(hello_txt);
    test_folder->addChild(hw);
    TA_folder->addChild(TA_folder_a_out);
    hw->addChild(TA_folder);
    hw->addChild(a_out);
    hw->addChild(hw1_cpp);
  }
  void TearDown() {
    delete hw;
    delete a_out;
    delete hw1_cpp;
    delete hello_txt;
    delete test_folder;
    delete TA_folder;
    delete TA_folder_a_out;
  }
  Folder* hw;
  Node* a_out;
  Node* hw1_cpp;
  File* hello_txt;
  Node* test_folder;
  Node* TA_folder;
  Node* TA_folder_a_out;
};

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}


TEST_F(NodeTest, AddException){
  ASSERT_ANY_THROW(hello_txt->addChild(test_folder));
}

TEST_F(NodeTest, CatchException){
  try{
    hello_txt->addChild(test_folder);
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Invalid add!", s);
  }
}

TEST_F(NodeTest, InfoByteFunctionOnFile){
//   ASSERT_EQ(14, infoByte(hello_txt));
}
TEST_F(NodeTest, InfoByteFunctionOnFolder){
//   ASSERT_EQ(19027, infoByte(hw));
}
TEST_F(NodeTest, ExistanceInfoNode){
  try{
    Node* a_out = new File("test/test_folder/hw/aw.out");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }
  try{
    Node* a_out = new Folder("test/test_folder/hww");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Node is not exist!", s);
  }
}
TEST_F(NodeTest, IteratorFromFolder) {
  Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(TA_folder, it->currentItem());
  it->next();
  ASSERT_EQ(a_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw1_cpp, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
  try{
    it->currentItem();
    ASSERT_TRUE(false);
  }
  catch(string s){
    ASSERT_EQ(s,"No current item!");
  }
  try{
    it->next();
  }
  catch(string s){
    ASSERT_EQ(s,"Moving past the end!");
  }
}
TEST_F(NodeTest,createNullIterator){
  try{
    Iterator * it = a_out->createIterator();
    it->first(); // Initialize
  }
  catch(string s){
    ASSERT_EQ(s,"no child member");
  }
  try{
    Iterator * it = a_out->createIterator();
    it->currentItem(); // Initialize
  }
  catch(string s){
    ASSERT_EQ(s,"no child member");
  }
  try{
    Iterator * it = a_out->createIterator();
    it->next(); // Initialize
  }
  catch(string s){
    ASSERT_EQ(s,"no child member");
  }
}
TEST_F(NodeTest,WrongTypeFile){
  try{
    Node* hw = new File("test/test_folder/hw");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("It is not File!", s);
  }
}
TEST_F(NodeTest, WrongTypeFolder){
  try{
   Node* a_out = new Folder("test/test_folder/hw/a.out");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("It is not Folder!", s);
  }
}
TEST_F(NodeTest, NameInfoNode){
  ASSERT_EQ("a.out", a_out->name());
  ASSERT_EQ("hw", hw->name());
}
TEST_F(NodeTest, IteratorFromFile){
  Iterator* it= hello_txt->createIterator();
  ASSERT_TRUE(it->isDone());
  try{
    it->first();
    ASSERT_EQ(true,false);
  }
  catch(string s){
    ASSERT_EQ(s,"no child member");
  }
}
TEST_F(NodeTest, ListNode){
  Utilities list;
  try{
   list.listNode(a_out);
   ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Not a directory", s);
  }
  ASSERT_EQ("TA_folder a.out hw1.cpp", list.listNode(hw));
}
TEST_F(NodeTest, FindNode){
  Utilities bla;
  ASSERT_EQ("a.out", bla.findNode(a_out,"a.out"));
  ASSERT_EQ("./TA_folder/a.out\n./a.out", bla.findNode(hw,"a.out"));
  ASSERT_EQ("",bla.findNode(hw,"hw"));
}

#endif
