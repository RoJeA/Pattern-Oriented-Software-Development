# Pattern Oriented Software Design
#### Fall, 2019
#### Dept. of Computer Science and Information Engineering
#### Taipei Tech
#### Homework 1

# Update
12 Sep 2019

# Purpose of the homework:
  Practice to write the unit test and makefile.
# Requirement:
1. Create `shape.h`, `circular_sector.h`, `triangle.h`, `ellipse.h` under the `src` folder .

    You should follow the classes below:

    **Note: Each class below are the skeleton. You should finish implementation by yourself.**
    
    `shape.h`
    
        class Shape
        {
            public:
            virtual double area() const = 0;
            virtual double perimeter() const = 0;
        }; 
    
    `circular_sector.h`
    
        class CircularSector:public Shape
        {
        public:
            CircularSector(double radius, double degree): _radius(radius), _degree(degree){}
            double area() const{}
            double perimeter() const{}

        };
        
    `triangle.h`
    
        class Triangle:public Shape
        {
        public:
            Triangle(double x1, double y1, double x2, double y2, double x3, double y3): _x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3){}
            // give you three points (x1,y1), (x2,y2), (x3,y3) to calculate area and perimeter
            double area() const{}
            double perimeter() const{}
            bool isIsoscelesTriangle(){}
        };
        
    `ellipse.h`
    
        class Ellipse:public Shape
        {
        public:
            Ellipse(double semiMajorAxes,double semiMinorAxes): _semiMajorAxes(semiMajorAxes), _semiMinorAxes(semiMinorAxes){}
            double area() const{}
            double perimeter() const{} // perimeter formula: 2π * semiMinorAxes + 4(semiMajorAxes-semiMinorAxes)
 
        };
        
2. Implement `area()` and `perimeter()` method for each class.

   ( If you need to use "pi", you should include <math.h> and use `M_PI` )

3. Implement the `isIsoscelesTriangle()` function in Triangle class.

        class Triangle:public Shape 
        {
        ...
            bool isIsoscelesTriangle()
        ...
        }
    
    You can only construct triangle class, when you want to buid a Isosceles Triangle.
    
    If it is not a IsoscelesTriangle, you should throw the `string` "Not a IsoscelesTriangle."

    `Note:`
        If it can not form a triangle, you also need to throw the `string` "Not a IsoscelesTriangle."

        class Triangle:public Shape 
        {
        ...
            Triangle(double x1, double y1, double x2, double y2, double x3, double y3):_x1(x1), _x2(x2), _x3(x3), _y1(y1), _y2(y2), _y3(y3)
            {
            ...
                if (...)
                {
                    throw ...;
                }
                ...

            }

            bool isIsoscelesTriangle(){}
        ...
        }
    

4. Write the unit test in `ut_shape.cpp` and put it under the `test` folder .

5. Write the corresponding makefile to generate executable file which named `ut_all` under the `bin` folder. 

# Note

Professor have push his code on the course repository.

You can refer to the source code under `shapes` folder at https://ssl-gitlab.csie.ntut.edu.tw/yccheng/posd2019f.

# Mark

TA assigned 10 test cases in CI.

Each test is 10 points, total is 100 points.


# Deadline
11:59 p.m. 19 Sep 2019

# File structure
This time your directory structure should be like:
 - 學號_HW
    - src

      shape.h

      ellipse.h

      circular_sector.h

      triangle.h

    - test

      ut_shape.cpp

    - bin

      ut_all

    - makefile



    `shape.h`, `ellipse.h`, `circular_sector.h`, `triangle.h` under `src` folder

    `ut_shape.cpp` under `test` folder

    `ut_all` under `bin` folder

Make sure your test on local is passed.Then you can push to gitlab and go to jenkins to check the report.