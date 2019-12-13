# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

#### Homework 3


# Update

  2 Oct 2019

# Purpose of the homework:
  Build a program to simulate command line application.
  
  Solve the problem 1: Sorting shapes

  The program of Homework3 is needed to sort shapes such as triangles, Ellipse, rectangles and others. 
  
  As a command line application, hw3 reads shapes from an input file, sorts the shapes by area or perimeter 
  
  in increasing order or decreasing order, and write the result to an output file. 
  
  For example:

      bin/geo input.txt output.txt area inc

  sorts the shapes in file input.txt in increasing order by area, and writes the result to the file output.txt. And

      bin/geo input.txt output.txt perimeter dec

  sorts the shapes in file input.txt in decreasing order by perimeter, and writes the result to the file output.txt.

  command line arguments:

  argument 1: path of input file.
  
  Note: (Don't modify the content in input.txt that we give you)

  argument 2: path of output file.
  
  Note: (You should write the result to output.txt)

  argument 3: the feature used for sorting (area or perimeter or sumOfSquares).

  argument 4: the ordering of feature, which could be inc or dec.
  
  If you need to get the useful token, you can try to use `Regular Expressions`.
  
  Using regular expression is easy to complete HW3.
  
  See [C++ Reference Regular Expressions](http://www.cplusplus.com/reference/regex/ )
  
# Requirements:
        
 1. Create `main.cpp` in src folder with following interface below. `main.cpp` will be compiled to `bin/geo`, and it will be the command line application.
        
        #include "terminal.h"

        int main(int argc, char *argv[]){
              // argv you can see makefile "bin/geo input.txt output.txt area inc"
              // argv[1] = input.txt, argv[2] = output.txt, argv[3] = area, argv[4] = inc 
              // implement reading input.txt
              // compose the string to Terminal(** Input string **)
              // **Input string**  Example: "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
              // call showResult() to get result
              // write the result to output.txt
              // Don't hard code!!!
        }

 2. Create `ut_main.cpp` in test folder with following interface below.

        #include <gtest/gtest.h>
        #include "ut_sort.h"
        
        int main(int argc, char ** argv)
        {
          testing::InitGoogleTest(&argc, argv) ;
          return RUN_ALL_TESTS() ;
        }
        
 3. Create `terminal.h` to simulate command line application with following interface below
 
        class Terminal
        {
        public:
            // you can use regular expression to get useful token from "Input string"
            Terminal(** Input string **)
            {
              // Input string like this => "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
                ....
            }

            std::string showResult()
            {
                ..... // return result For example: [XXX, XXX, XXX]
            }
        }
        
 4. write the test in `ut_sort.h` that you should test "showResult()" 
    
        TEST(TerminalTest, AreaDescending)
        {
          Terminal * test = new Terminal("Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area dec");
          ASSERT_EQ("[12.000000, 6.000000]", test->showResult());
        }
        
        ...
 
 5. `Input string` above is consisted of arguments.
 
    The format of `Input string` is `[shapes] [feature] [order]`

    `[shapes]` : There must be space `' '` between shape and paren`()`.
    
    Note: Space between class name and left round bracket.
    
    For example:
        
        Ellipse (6,5)
    
    Different shapes you want sort, and each shape will be seperated by space `' '`
    
    For example: 
    
        Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40)
        
    
    `[feature]` : the feature used for sorting (area or perimeter or sumOfSquares)
                 
    `[order]`  : the ordering of feature, which could be inc or dec
    
                inc : `Ascending`
                
                dec : `Descending`
    
    **Different type of argument will also be seperated by space `' '`**
    
    Total `Input string` will be 
    
        Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc
 
 6. Get the result of `Input string` by calling `showResult()`
 
    Input string 

        Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc

    Result will be the size of area of the shapes sorted ascendingly as below:    
        
        [6.000000, 22.340214, 94.247780]
 
 7. The open paren`(` will always be with close paren`)`

    In the paren`()`, arguments will be seperated by comma`,`
    
    It's possible to put some space`' '` in the paren`()`,
    
    This input are valid:
    
        Ellipse (6  ,   5) Triangle (3  ,0    ,  0  , 2,  -3,0) CircularSector (8  ,  40) area inc
    
    show result 
        
        [6.000000, 22.340214, 94.247780]
 
 8. Invalid argument will be skipped such as !@#$%^^<>?, not arg, etc.
  
    **Special character in Input string **
    
    For example:

        Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc !@#$%%
        
    or
        
        Ellipse (6,5) Triangle (3,0,0,2,-3,0) !@#$%% CircularSector (8,40) area inc
        
    can also show result 
        
        [6.000000, 22.340214, 94.247780]
    
    !@#$%% is unuseful token that should be skipped
 
 9. Invalid shapes will be skipped
 
    **Shape name is against the rules.**

    That first character of Shape name should be `Upcase`
    
    For example:

        Ellipse (6,5) triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc
    
    triangle (3,0,0,2,-3,0) => Shape name `triangle` first character is lowercase, so `triangle (3,0,0,2,-3,0)` should be skipped
    
    show result 
        
        [22.340214, 94.247780]
        
    or
    
    Special character should not in Shape
    
    For example:
    
        Ellipse (6,5) Triangle!@#$%% (3,0,0,2,-3,0) CircularSector (8,40) area inc
    
    `Triangle!@#$%% (3,0,0,2,-3,0)` contain special character `Triangle!@#$%% (3,0,0,2,-3,0)` should be skipped
        
    show result 
        
        [22.340214, 94.247780]
        
        
    **Number of arugument is wrong.**
    
    Number of arugument:
    
    Triangle => 6
    
    Ellipse => 2
    
    CircularSector => 2
    
    For example:

        Ellipse (6,5) Triangle (3,0,0) CircularSector (8,40) area inc
    
    Triangle (3,0,0) lost 3 aruguments, so Triangle should be skipped
    
    The result will be
    
        [22.340214, 94.247780]
        
    **Type of arugument is wrong.**
    
    For example:

        Ellipse (6,5) Triangle (3,0,0,2,-3,zero) CircularSector (8,40) area inc
        
    Triangle (3,0,0,2,-3,zero) contains "zero' zero is wrong type, so Triangle should be skipped 
    
    If arugument contain any `wrong type`(not number), Shape should be skipped
    
    The result will be
    
        [22.340214, 94.24778]

 10. Incomplete `Input string` will throw exception.
 
    For example:

        Ellipse(6,5) triangle(3,0,0,2,-3,0) CircularSector(8,40) area
    
    because User Input does not contain `inc` or `dec` program can not sort
    
    This condition you should throw `string` "Unuseful User Input!" in showResult()
        

 11. `Input string` specification should follow:

        Ellipse (9,8) Triangle (0,0,5,0,0,5) CircularSector (9, 35)

        ※ Note: you must add a white space between class name and left round bracket.


 12. output.txt data specification should follow:

      Run the command line:  
      `bin/geo input.txt output.txt area inc`  
      The result in output.txt should be: 

        [12.500000, 24.740042, 226.194671]


 11. Put "TA's makefile" and "input.txt" into your folder 學號_HW " makefile and input.txt" don't modify
 
 12. Make sure your project structure should be the same as following
    - 學號_HW
        - src
    
          circular_sector.h
    
          ellipse.h
    
          main.cpp
    
          shape.h
    
          sort.h
    
          terminal.h

          triangle.h
          
        - test
          
          ut_main.cpp
    
          ut_sort.h
    
        - bin
    
          ut_all
          
          geo
        
        - input.txt
        
        - makefile
        
        - output.txt
 
 
# Mark

TA assigned 10 test cases in CI.

# Deadline
11:59 p.m. 2 oct 2019

# Note
Make sure your tests on local are all pass. Then you can push to Gitlab and watch the report on Jenkins.