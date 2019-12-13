# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

#### Homework 6
# Homework Outline
* [Purpose of the homework](#purpose-of-the-homework)
* [Requirements](#requirements)
* [File structure](#file-structure)
* [Grading rubrics](#grading-rubrics)
* [Deadline](#deadline)
* [Note](#note)
# Purpose of the homework
Practice visitor and proxy pattern.
1. implement Link.
2. implement FindVisitor and UpdatePathVisitor.
3. implement getPath().
4. implement renameNode().

# Requirements
 1. Use iterator implemented in last homwork.
    (You can refer to Professor's website [course project directory](https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f).)
 
 2. Use proxy pattern to implement Link.
 
        class Link {
        public:
          Link(string path, Node * node); // You should check path if it is not a link that you should throw string "It is not Link!"
        
          void accept(***visitor***); // aceep visitor
        
          void addLink(Node * node); // add symbolic link
        
          Node * getSource(); // return node that the link point to!
        
          Iterator* createIterator(); // return null Iterator

        };
  
 3. Throwing an exception as hw4 if your path of constructor does not correspond with your class or the node doesn't exist.

        TEST (FileSystemTest, NodeTypeError)
        {
          ASSERT_ANY_THROW(new File("./123")); //If the node doesn't exist, you should throw string "Node is not exist!"
          ASSERT_ANY_THROW(new File("./test_data/folder")); //If the File doesn't exist, you should throw string "It is not File!"
          ASSERT_ANY_THROW(new Folder("./test_data/hello")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
          ASSERT_ANY_THROW(new Link("./test_data/test", a_out)); //If the Link doesn't exist, you should throw string "It is not Link!"
        }
        
 4. Implement `getPath()` for Node Class.

        string getPath()
        {
            // Getter!
            // return node path
        }

 5. Create the Visitor class in visitor.h, and Visitor class is an abstract class and is represented as a Visitor in Visitor pattern. 

        class Visitor
        {
          public:
              virtual void visitFolder(Folder * folder) = 0;
              virtual void visitFile(File * file) = 0;
              virtual void visitLink(Link * link) = 0;
        };

 6. Create the FindVisitor in find_visitor.h and find_visitor.cpp.
  
    **Note:** 

    Make sure FindVisitor inheriates Visitor class. 

        class FindVisitor
        {
            public:
                FindVisitor(string name); // Name is the target we want to find.
                void visitFolder(Folder * folder);
                void visitFile(File * file);
                void visitLink(Link * link); // You only need to check the link itself,and you don't have to check the node that the link point to!  
                string findResult();
        };

 7. Feature of `FindVisitor` is similar to `findNode(Node* node, string name)` in hw5.

    `findResult()` is to get the result after `FindVisitor` traverse the file system and get those nodes that satisfy the condition.

    For example:`a.out` in different folders

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *test_data/`a.out`*

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*test_data/folder/`a.out`*

        FindVisitor * fv = new FindVisitor("a.out");
       
        test_data->accept(fv);

    And the result of `fv->findResult()` should be:

        ./a.out\n./folder/a.out

 8. You can use the same FindVisitor `more than one time`, so you should initialize the status each time.

    For example:`a.out` in different folders

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *test_data/`a.out`*

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*test_data/folder/`a.out`*

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *test_different_data/`a.out`*

          FindVisitor * fv = new FindVisitor("a.out");
          test_data->accept(fv);
          string result1 = fv->findResult() //result1 will be "./a.out\n./folder/a.out"
          test_different_data->accept(fv);
          string result2 = fv->findResult() //result2 will be "./a.out"


 9. Implement `renameNode()` for Node Class.
  
        void renameNode(string new_name)
        {
          /* You should update 
            1. The physical node name.
            2. The node name in your own file system
          */
        }
    
    For example: `a.out` in test_data folders

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *test_data/`a.out`*
        
        struct staUpdatePathVisitor;
        UpdatePathVisitor * upv = new UpdatePathVisitor();
        a_out = new File("test_data/a.out");
        a_out->renameNode("TA_file");
        a_out->accept(upv);
        ASSERT_EQ("TA_file", a_out->name()); // Check the node name in your own file system!
        if (lstat("test_data/TA_file", &_st) != 0)
            FAIL(); // Check the physical node name!
        
 10. Create the UpdatePathVisitor in update_path_visitor.h and update_path_visitor.cpp.
    
    class UpdatePathVisitor
    {
        public:
            UpdatePathVisitor();
            void visitFolder(Folder * folder);
            void visitFile(File * file);
            void visitLink(Link * link);
    };
  
**Note:** 

Make sure UpdatePathVisitor inheriates Visitor class. 

You should use the UpdatePathVisitor to update the path after calling `renameNode()`

(Update the path of `itself` and `its child node`!)

For example: 

Original file structure

```
- test_data
    - gp
        - a.out
```

After calling `renameNode()` 

```
- test_data
    - TA_folder
        - a.out
```
Below is assertion!

        struct stat _st;
        UpdatePathVisitor * upv = new UpdatePathVisitor();
        test_data = new Folder("test_data");
        gp = new Folder("test_data/gp");
        a_out = new File("test_data/gp/a.out");
        test_data->addChild(gp);
        gp->addChild(a_out);
        // SetUp
        
        gp->renameNode("TA_folder");
        ASSERT_EQ("TA_folder", gp->name()); // Check the node name in your own file system!
        
        gp->accept(upv); 
        /* 
            Accept the UpdatePathVisitor to  update the node path in your own file system!
            UpdatePathVisitor should update the path of itself and its child node!
        */
        
        ASSERT_EQ("test_data/TA_folder", gp->getPath()); // Check the path of itself!
        ASSERT_EQ("test_data/TA_folder/a.out", a_out->getPath()); // Check the path of child node!
        
        if (lstat("test_data/TA_folder", &_st) != 0)
            FAIL(); // Check the physical node name!
            
 11. You can use the same UpdatePathVisitor `more than one time`, so you should initialize the status each time..

 12. Write the corresponding makefile to generate executable file which named `ut_all` in bin folder.

#### File structure:
`ut_main.cpp` should include "ut_fs.h"

```
- bin
    - ut_all
- obj
    - find_visitor.o
    - update_path_visitor.o
- src
    - file.h
    - find_visitor.cpp
    - find_visitor.h
    - folder.h
    - iterator.h
    - link.h
    - node.h
    - null_iterator.h
    - update_path_visitor.cpp
    - update_path_visitor.h
    - visitor.h
- test
    - test_folder
    - ut_fs.h
    - ut_main.cpp
makefile
```

# Grading rubrics

TA assigned 16 test cases in CI.

# Deadline
11:59 p.m. 20 Nov 2019

# Note
Make sure your all tests pass on your local machine. 
Then you can push to Gitlab and see the report on Jenkins.