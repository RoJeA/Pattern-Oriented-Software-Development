#ifndef UT_FILE_H
#define UT_FILE_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"

TEST(StatApi, GetSize) {
  struct stat st;
  ASSERT_EQ(0, stat("test/test_folder/hello.txt", &st));
  int size = st.st_size;
  ASSERT_EQ(14, size);
}

TEST(FileTest, First) {
  File hello_txt("test/test_folder/hello.txt");
  ASSERT_EQ(14, hello_txt.size());
}

// TEST(FolderTest, Second) {
//   File hello_txt("test/test_folder/hello.txt");
//   Folder test_folder("test/test_folder");
//   ASSERT_EQ(512, test_folder.size());
//   test_folder.addChild(&hello_txt);
//   ASSERT_EQ(14, test_folder.getChild(0)->size());
//
//   Folder hw("test/test_folder/hw");
//   test_folder.addChild(&hw);
//   ASSERT_EQ(512, test_folder.getChild(1)->size());
// }

TEST(FileTest, AddException){
  File hello_txt("test/test_folder/hello.txt");
  Folder test_folder("test/test_folder");
  ASSERT_ANY_THROW(hello_txt.addChild(&test_folder));
}

TEST(FileTest, CatchException){
  File hello_txt("test/test_folder/hello.txt");
  Folder test_folder("test/test_folder");
  try{
    hello_txt.addChild(&test_folder);
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Invalid add!", s);
  }
    // catch(int i){}
}

TEST(FileTest, InfoByteOnFile){
  Node* hello_txt = new File("test/test_folder/hello.txt");
  ASSERT_EQ(14, hello_txt->infoByte());
}

TEST(FolderTest, InfoByteOnFolder){
  Node* hw = new Folder("test/test_folder/hw");
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ(19027, hw->infoByte());
}

// TEST(FileTest, InfoByteFunctionOnFolder){
//   Node* hw = new Folder("test/test_folder/hw");
//   Node* a_out = new File("test/test_folder/hw/a.out");
//   Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
//   hw->addChild(a_out);
//   hw->addChild(hw1_cpp);
//   ASSERT_EQ(19027, infoByte(hw));
// }

TEST(NodeTest, ExistanceInfoNode){
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

TEST(FileTest,WrongTypeFile){
  try{
    Node* hw = new File("test/test_folder/hw");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("It is not File!", s);
  }
}

TEST(FolderTest, WrongTypeFolder){
  try{
   Node* a_out = new Folder("test/test_folder/hw/a.out");
    ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("It is not Folder!", s);
  }
}
TEST(NodeTest, NameInfoNode){
  Node* a_out = new File("test/test_folder/hw/a.out");
  ASSERT_EQ("a.out", a_out->name());

  Node* hw = new Folder("test/test_folder/hw");
  ASSERT_EQ("hw", hw->name());
}
TEST(NodeTest, FindNode){
   Node* hw = new Folder("test/test_folder/hw");
   Node* a_out = new File("test/test_folder/hw/a.out");
   Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
   Node* TA_folder = new Folder("test/test_folder/hw/TA_folder");
   Node* TA_folder_a_out = new File("test/test_folder/hw/TA_folder/a.out");
   ASSERT_EQ("a.out", a_out->findNode("a.out"));
   hw->addChild(a_out);
   hw->addChild(hw1_cpp);
   hw->addChild(TA_folder);
   TA_folder->addChild(TA_folder_a_out);
   ASSERT_EQ("./hw1.cpp", hw->findNode("hw1.cpp"));
   ASSERT_EQ("./a.out\n./TA_folder/a.out", hw->findNode("a.out"));
}
TEST(NodeTest, ListNode){
  try{
   Node* a_out = new File("test/test_folder/hw/a.out");
   a_out->listNode();
   ASSERT_EQ(true, false);
  } catch(std::string s){
    ASSERT_EQ("Not a directory", s);
  }

  Node* hw = new Folder("test/test_folder/hw");
  Node* a_out = new File("test/test_folder/hw/a.out");
  Node* hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
  hw->addChild(a_out);
  hw->addChild(hw1_cpp);
  ASSERT_EQ("a.out hw1.cpp", hw->listNode());
}

#endif
