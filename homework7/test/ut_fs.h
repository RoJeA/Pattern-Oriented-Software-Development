#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/link.h"
#include "../src/find_visitor.cpp"
#include "../src/filesystem_builder.cpp"

TEST (FileSystemTest, NodeTypeError)
{
  ASSERT_ANY_THROW(new File("./123")); //If the node doesn't exist, you should throw string "Node is not exist!"
  ASSERT_ANY_THROW(new File("./test_data/folder")); //If the File doesn't exist, you should throw string "It is not File!"
  ASSERT_ANY_THROW(new Folder("./test_data/hello")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
  ASSERT_ANY_THROW(new Link("./test_data/test")); //If the Link doesn't exist, you should throw string "It is not Link!"
}

TEST(FileSystemBuilder, Singleton){
  FileSystemBuilder * fsb1 = FileSystemBuilder::instance();
  FileSystemBuilder * fsb2 = FileSystemBuilder::instance();
  ASSERT_EQ(fsb1,fsb2);
}

TEST(FileSystemBuilder, file){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hw/a.out");
  ASSERT_EQ("a.out", fb->getRoot()->name());
  ASSERT_EQ("test/test_folder/hw/a.out", fb->getRoot()->getPath());
}
TEST(FileSystemBuilder, folder){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("test/test_folder/hw");
  ASSERT_EQ("hw", fb->getRoot()->name());
  ASSERT_EQ("test/test_folder/hw", fb->getRoot()->getPath());
}
TEST(FileSystemBuilder, link){
  FileSystemBuilder * fb = FileSystemBuilder::instance();
  fb->build("./junklink");
  ASSERT_EQ("junklink", fb->getRoot()->name());
  ASSERT_EQ("./junklink", fb->getRoot()->getPath());
}


#endif
