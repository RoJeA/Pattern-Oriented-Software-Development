# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech

#### Homework 2

# Update
20 Sep 2019

# Purpose of the homework:
  Different ways to pass compare function
  1. lambda function
  2. function
  3. object
  
  Implement quicksort and Using different ways to pass compare function

  See [C++ Reference std::sort](http://www.cplusplus.com/reference/algorithm/sort/ "std::Sort")

  See [C++ Reference vector iterator](http://www.cplusplus.com/reference/vector/vector/begin/ )

# Requirements:
 1. Modify `shape.h`. with following interface below.

        class Shape {
        ...
            virtual double area() const = 0;
            virtual double perimeter() const = 0;
            virtual double sumOfSquares() const = 0;
        
        ...
        }

 2. Implement `sumOfSquares()` method for `each class`.

        sumOfSquares Formula : area ^2 + perimeter ^2


 3. Create `sort.h`. with following interface below:

    **Note: Each class constructor below are the skeleton. You should finish implementation by yourself.**

        class Sort{
            public:
              Sort(std::vector<Shape*>* v): _v(v){}

              // The argument ** Accept comparison ** can accept lambda, function, and object
              void sortArea(** Accept comparison **)
                // you can use std:sort in this function

              void sortPerimeter(** Accept comparison **)
                // you can use std:sort in this function

              void sortSumOfSquares(** Accept comparison **)
                // you can use std:sort in this function

              void quickSort(** Accept comparison **)
                // quickSort() function should be function template
                // You should write the quickSort by yourself!
                // In the loop of the quickSort algorithm, use Iterator to control your vector rather than index.
                ***
                Example:
                    for ( std::vector<...>::iterator it ... )
                ***

            private:
              std::vector<Shape*>* _v;
        };
        
        // implement following call back function
        
        bool areaAscendingComparison(Shape *a, Shape *b){...};

        bool areaDescendingComparison(Shape *a, Shape *b){...};
        
        class AscendingComparison{
            AscendingComparison(string XXX){...}
        };
        
        class DescendingComparison{
            DescendingComparison(string XXX){...}
        };
        
        

    **You should implement ascending descending `lambda function` as parameter for Sort::sortArea(), Sort::sortPerimeter(), Sort::sortSumOfSquares(), Sort::quickSort()**

    **You should use following functions as parameter for Sort::sortArea(), Sort::quickSort()**
        
        bool areaAscendingComparison(Shape *a, Shape *b){...};

        bool areaDescendingComparison(Shape *a, Shape *b){...};
        


    **You should use following objects as parameter for Sort::sortArea(), Sort::sortPerimeter(), Sort::sortSumOfSquares(), Sort::quickSort()**
            
        class AscendingComparison{
            AscendingComparison(string XXX){...}
          
            *** You should use "xxx" to identify Comparison ***
          
            For example:
              string xxx is `area` that your operator should compare `area`
            
              string xxx is `perimeter` that your operator should compare `perimeter`
            
              string xxx is `sumOfSquares` that your operator should compare `sumOfSquares`
        };

        class DescendingComparison{
            DescendingComparison(string XXX){...}
            
            *** You should use "xxx" to identify Comparison ***
              
              For example:
                string xxx is `area` that your operator should compare `area`
                
                string xxx is `perimeter` that your operator should compare `perimeter`
                
                string xxx is `sumOfSquares` that your operator should compare `sumOfSquares`
        };
    
        
    For example:
        
            vector<Shape*> shapes(....);
            Sort* sort = new Sort(&shapes);
            AscendingComparison ascendingComparison("area");
            sort->sortArea(ascendingComparison);
              
    shapes will be sorted by area ascendingly by the above code        
        
    **Note:  In the loop of the `quickSort` algorithm, use `std::vector<Shape*>::Iterator` to control your vector rather than index.**
    **You should implement quickSort() as function template**
    **We will pass following comparison function you wrote to quickSort() function to test.**
             
             For example:
                 Pass `areaAscendingComparison()` function to quickSort(), then the shapes will be sorted ascendingly by area. 
                 Pass `sumOfSquaresAscendingComparison` object to quickSort(), then the shapes will be sorted ascendingly by sumOfSquares.
                 Pass `lambdafunction` to quickSort()...
                 ...

 4. Create `main.cpp` under `src` folder, `ut_sort.h` under `test` folder.<br>
 The `main.cpp` should include `ut_sort.h`.<br>
 Write the sort unit test in `ut_sort.h`.<br>

 5. Write the corresponding makefile to generate executable file which named **`bin/ut_all`**.
 
    Modify makefile, and when program encounter many errors terminal will show only `First Error`.

    For example:
    
          Following Errors on terminal
          
            src/../test/ut_sort.h:206:6: error: redefinition of ‘class ShapeTest_QuickSortClass_Test’
             TEST(ShapeTest, QuickSortClass)
                  ^
            src/../test/ut_sort.h:191:6: note: previous definition of ‘class ShapeTest_QuickSortClass_Test’
             TEST(ShapeTest, QuickSortClass)
                  ^
            src/../test/ut_sort.h:206:1: error: redefinition of ‘testing::TestInfo* const ShapeTest_QuickSortClass_Test::test_info_’
             TEST(ShapeTest, QuickSortClass)
             ^
            src/../test/ut_sort.h:191:6: note: ‘testing::TestInfo* const ShapeTest_QuickSortClass_Test::test_info_’ previously declared here
             TEST(ShapeTest, QuickSortClass)
                  ^
            src/../test/ut_sort.h:206:6: error: redefinition of ‘void ShapeTest_QuickSortClass_Test::TestBody()’
             TEST(ShapeTest, QuickSortClass)
           
       `After modify makefile it can show only first error`
        
        src/../test/ut_sort.h:206:6: error: redefinition of ‘class ShapeTest_QuickSortClass_Test’
         TEST(ShapeTest, QuickSortClass)
       
       
 6. Make sure your project structure should be the same as following
    - 學號_HW
        - src
    
          circular_sector.h
    
          ellipse.h
    
          main.cpp
    
          shape.h
    
          sort.h
    
          triangle.h
    
        - test
    
          ut_sort.h
    
        - bin
    
          ut_all
    
        - makefile

# Mark

TA assigned 13 test cases in CI.

# Deadline
11:59 p.m. `(Wednesday) 25 Sep` 2019

# Note
Make sure your tests on local are all pass. Then you can push to Gitlab and watch the report on Jenkins.
