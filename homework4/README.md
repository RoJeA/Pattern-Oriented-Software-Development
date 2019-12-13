# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

#### Homework 4

# Purpose of the homework:
  Practice composite pattern.

  You can reference Professor's website https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f to implement following methods
  
  (You can modify method or add new method by yourself)
  
  Don't use `global function or global variable`!
  
  1. `name()`  
  
  2. `findNode()` 
  
  3. `listNode()` 

      The `findNode()` method is just like `find -name XXXX` command in linux.
      
      The `listNode()` method is just like `ls` command in linux.
  
  
# Requirements:
 1. You can reference Professor's website https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f
 
 2. Give you `path` that you should check the node is exist or not 
 
    If it is not exist you should throw "Node is not exist!"
    
     For example:

        Node * a_out = new File("test/TA_folder/hw/Not_exist_file");
    
    If new File("XXXX")/new Folder("XXX") you should check the node is file/folder
    
    If it is not file you should throw "It is not File!"
    
    For example:

        Node * a_out = new File("test/TA_folder/hw/TA_Folder");
    
    If it is not folder you should throw "It is not Folder!"
    
    For example:
    
        Node * a_out = new Folder("test/TA_folder/hw/TA_File");
 3. Implement `name()` and `findNode()` and `listNode()` method for File, Folder, Node class.

        std::string name()
        {
              // For example path:"test/TA_folder/hello.txt"
              // "hello.txt" is name
              // Return "hello.txt"
        }
        
        std::string findNode(std::string name)
        {
              // implementation findNode
              // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it. 
              // file->findNode(name) that should find itself.
              // if find two nodes or more than two nodes.
              // Result should be separated by '\n'. 
              
        }
        
        std::string listNode()
        {
              // implementation list child Node and Sort by dictionary
              // Result should be separated by space
              // For example: 
              // Folder contains childnode "a.out" and "TA_folder" and "hello.txt"
              // It should return "TA_folder a.out hello.txt"
              // If node is file, it can't listNode.
              // It should throw "Not a directory"
              // For Example: TA_file->listNode()
        }

      **Note**  
      `File->findNode(std::string nodeName)` should return the file name if the file was found.

            ASSERT.EQ("a.out",a_out->findNode("a.out"));

 
 4. **There is a situation you should be known. The fileSystem can have the same file/folder name in the different folder.**
 
    **Your answer should be all the paths seperated by '\n'. Just like linux find multipath.**

      *Example: `a.out` in different folders*

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; *test_data/`a.out`*

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*test_data/folder/`a.out`*

    And your answer of  `test_data->findNode('a.out')` should be:

        ./a.out\n./folder/a.out

    And the assertion should be:

        ASSERT.EQ("./a.out\n./folder/a.out", test_data->findNode("a.out"));

      Note

      The `findNode()` result is same as using the `find -name a.out` command in linux.
 
 5. listnode() Your answer should be all Nodenames seperated by ' '. Just like `ls` command in linux.
    
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; test_data/`a.out`

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;test_data/`TA_folder`
    
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;test_data/`hello.txt`
    
    and your answer of  `test_data->listNode()` should be:

        TA_folder a.out hello.txt

    And the assertion should be:

        ASSERT.EQ("TA_folder a.out hello.txt", test_data->listNode());
    
 
 5. Write the corresponding makefile to generate executable file which named **`ut_all`** in bin folder.

#### File structure:
`ut_main.cpp` should include "ut_node.h"

```
- bin
    - ut_all
- src
    - file.h
    - folder.h
    - node.h
- test
    - test_folder
    - ut_main.cpp
    - ut_node.h
makefile
```

# Grading rubrics

TA assigned 12 test cases in CI.

# Deadline
11:59 p.m. 17 oct 2019

# Note
Make sure your all tests pass on your local machine. Then you can push to Gitlab and see the report on Jenkins.