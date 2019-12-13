# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech
#### Homework 5

# Update
23 Oct 2019

#### Homework 5

# Purpose of the homework:

####  Use the [course material](https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f) to implement Iterator Pattern.

####  Change the data structure `std::vector<Node *>`  into `std::map<string, Node *>` and refactor related member functions.
# Requirements:
 1. Add Test Setup and Test Teardown in UnitTest.
 2. In Folder class, you must change the the data structure `std::vector<Node *>` into `std::map<string,Node *>` and make sure member functions in Folder class work correctly afterwards.
 
    **Note:** You must use filename as your key in `std::map<string, Node *>`
 
 3. Create the Iterator class in iterator.h . Move innerclass Iterator from class Node to iterator.h.
    In iterator.h, you can use following code and #include guard.
    You should not include node.h to avoid some condition. Write 'class Node' instead.

        class Node;
        class Iterator
        {
        public:
          virtual void first() = 0;
          virtual Node* currentItem() = 0;
          virtual void next() = 0;
          virtual bool isDone() = 0;
        };

 4. Modify createIterator() function to be `virtual Iterator *createIterator() = 0;` in  `Node` class
 5. Create the inner class `FolderIterator`  in folder class and `FolderIterator` should inherit `Iterator`
 
        class FolderIterator : public XXXX
         {
          public:
            FolderIterator(Folder * f){}
            void first()
            {
              // initialization
            }
            Node* currentItem()
            {
              // if iterator is to the end that it should throw string "No current item!"
              // if iterator is not to the end that it should return current node
            }
            void next()
            {
              // if iterator is to the end that it should throw string "Moving past the end!"
              // if iterator is not to the end that it should add 1
            }
            bool isDone()
            {
              // return iterator is to the end or not?
            }
        }

 6. Create NullIterator in null_iterator.h and it should inherit `Iterator`, where the member function `isDone()` must return true.
    Remove innerclass NullIterator in Node class. 
 
    **Note:** The File class call createIterator() must return NullIterator.

        class NullIterator:public XXX
        {
          public:
            void first(){
              //throw string "no child member"
            }
            Node* currentItem(){
              //throw string "no child member"
            }
            void next() {
              //throw string "no child member"
            }
            bool isDone(){
              return true;
            }
        };
  
 7. Create utilities.h and class Utilities
    
        class Utilities 
        {
            public:
                string listNode(Node* node)
                {
                    // You should use iterator pattern to access node in folder!
                    // You can use dynamic_cast if you need
                    // If node is file that it should throw string "Not a directory"
                    // This function is same as Hw4 listNode()
                }
    
                string findNode(Node* node, string name)
                {
                    // You should use iterator pattern to access node in folder!
                    // You can use dynamic_cast if you need
                    // This function is same as Hw4 findNode()
                }
        };
  
            
 8.Write the corresponding makefile to generate executable file which named `bin/ut_all` in bin folder.

#### File structure:
`ut_main.cpp` should include "ut_fs.h"

```
- bin
    - ut_all
- src
    - file.h
    - folder.h
    - node.h
    - iterator.h
    - null_iterator.h
    - utilities.h
- test
    - test_folder
    - ut_main.cpp
    - ut_fs.h
makefile
```

# Grading rubrics

TA assigned 12 test cases in CI.

# Deadline
11:59 p.m. 30 Oct 2019

# Note
Make sure your all tests pass on your local machine. Then you can push to Gitlab and see the report on Jenkins.