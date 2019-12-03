#ifndef UT_SORT_H
#define UT_SORT_H

#include<gtest/gtest.h>
#include"../src/shape.h"
#include"../src/circular_sector.h"
#include"../src/ellipse.h"
#include"../src/triangle.h"
#include"../src/sort.h"
#include<algorithm>

//First Test
TEST(HelloTest,First)
{
  ASSERT_EQ("Hi,First Test","Hi,First Test");
}
//Pure Sort
TEST(SortTest, Sorting)
{
 Shape* test_array[6] = {new CircularSector(2,180), new CircularSector(5,72), new Ellipse(6,3), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Triangle(0,0,1,0,0,1)};
//2*pi                       //5*pi                   //18*pi             //3*pi            //3.5   //-1              //0.5
 vector<Shape*>* ShapeInfo = new vector<Shape*>;
 for (int i=0; i<6; i++)
 {
   ShapeInfo->push_back(test_array[i]);
 }
 Sort s(ShapeInfo);
 s.sortArea(areaAscendingComparison);
 ASSERT_NEAR(0.5, ShapeInfo->at(0)->area(), 0.001);
 ASSERT_NEAR(3.5, ShapeInfo->at(1)->area(), 0.001);
 ASSERT_NEAR(2*3.14159, ShapeInfo->at(2)->area(), 0.001);
 ASSERT_NEAR(3*3.14159, ShapeInfo->at(3)->area(), 0.001);
 ASSERT_NEAR(5*3.14159, ShapeInfo->at(4)->area(), 0.001);
 ASSERT_NEAR(18*3.14159, ShapeInfo->at(5)->area(), 0.001);
//Sort perimeter
ShapeInfo->clear();
 for (int i=0; i<6; i++)
 {
   ShapeInfo->push_back(test_array[i]);
 }
 Sort p(ShapeInfo);
 p.sortPerimeter(perimeterDescendingComparison);
  ASSERT_NEAR(30.849, ShapeInfo->at(0)->perimeter(), 0.001);
  ASSERT_NEAR(16.283, ShapeInfo->at(1)->perimeter(), 0.001);
  ASSERT_NEAR(14.283, ShapeInfo->at(2)->perimeter(), 0.001);
  ASSERT_NEAR(11.414, ShapeInfo->at(3)->perimeter(), 0.001);
  ASSERT_NEAR(10.283, ShapeInfo->at(4)->perimeter(), 0.001);
  ASSERT_NEAR(3.414, ShapeInfo->at(5)->perimeter(), 0.001);
}
//Class Sort
TEST(ClassTest, ObjectSorting)
{
  Shape* test_array[6] = {new CircularSector(2,180), new CircularSector(5,72), new Ellipse(6,3), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort C(ShapeInfo);
  AscendingComparison cac("area");
  C.sortArea(cac);
  ASSERT_NEAR(0.5, ShapeInfo->at(0)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(5)->area(), 0.001);

  AscendingComparison cpc("perimeter");
  C.sortPerimeter(cpc);
  ASSERT_NEAR(30.849, ShapeInfo->at(5)->perimeter(), 0.001);
  ASSERT_NEAR(16.283, ShapeInfo->at(4)->perimeter(), 0.001);
  ASSERT_NEAR(14.283, ShapeInfo->at(3)->perimeter(), 0.001);
  ASSERT_NEAR(11.414, ShapeInfo->at(2)->perimeter(), 0.001);
  ASSERT_NEAR(10.283, ShapeInfo->at(1)->perimeter(), 0.001);
  ASSERT_NEAR(3.414, ShapeInfo->at(0)->perimeter(), 0.001);
}
TEST(AreaAscendingFunction,areaSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort AAF(ShapeInfo);
  AscendingComparison aaf("area");
  AAF.sortArea(aaf);
  ASSERT_NEAR(0.5, ShapeInfo->at(0)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(5)->area(), 0.001);
}
TEST(AreaAscendingLambda,areaSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort AA(ShapeInfo);
  AA.sortArea(areaAscendingComparison);//Function
  ASSERT_NEAR(0.5, ShapeInfo->at(0)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(5)->area(), 0.001);
}
TEST(AreaDescendingClass,areaSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort AD(ShapeInfo);
  DescendingComparison ad("area");
  AD.sortArea(ad);
  ASSERT_NEAR(0.5, ShapeInfo->at(5)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(0)->area(), 0.001);
}
TEST(AreaDescendingFunction,areaSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort AD(ShapeInfo);
  DescendingComparison ads("area");
  AD.sortArea(ads);
  ASSERT_NEAR(0.5, ShapeInfo->at(5)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(0)->area(), 0.001);
}
TEST(AreaDescendingLambda,areaSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort AD(ShapeInfo);
  AD.sortArea(areaDescendingComparison);//Function
  ASSERT_NEAR(0.5, ShapeInfo->at(5)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(0)->area(), 0.001);
}
TEST(PerimeterAscendingLambda,perimeterSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort PD(ShapeInfo);
  PD.sortPerimeter([](Shape *x,Shape *y){
    return x->perimeter() < y->perimeter();
  });//[]Function
  ASSERT_NEAR(30.849, ShapeInfo->at(5)->perimeter(), 0.001);
  ASSERT_NEAR(16.283, ShapeInfo->at(4)->perimeter(), 0.001);
  ASSERT_NEAR(14.283, ShapeInfo->at(3)->perimeter(), 0.001);
  ASSERT_NEAR(11.414, ShapeInfo->at(2)->perimeter(), 0.001);
  ASSERT_NEAR(10.283, ShapeInfo->at(1)->perimeter(), 0.001);
  ASSERT_NEAR(3.414, ShapeInfo->at(0)->perimeter(), 0.001);
}
TEST(PerimeterDescendingLambda,perimeterSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort PD(ShapeInfo);
  PD.sortPerimeter([](Shape *x,Shape *y){
    return x->perimeter() > y->perimeter();
  });//[]Function
  ASSERT_NEAR(30.849, ShapeInfo->at(0)->perimeter(), 0.001);
  ASSERT_NEAR(16.283, ShapeInfo->at(1)->perimeter(), 0.001);
  ASSERT_NEAR(14.283, ShapeInfo->at(2)->perimeter(), 0.001);
  ASSERT_NEAR(11.414, ShapeInfo->at(3)->perimeter(), 0.001);
  ASSERT_NEAR(10.283, ShapeInfo->at(4)->perimeter(), 0.001);
  ASSERT_NEAR(3.414, ShapeInfo->at(5)->perimeter(), 0.001);
}
TEST(SumOfSquaresAscendingClass,sumOfSquaresSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort SC(ShapeInfo);
  AscendingComparison sc("sumOfSquares"); //Object
  SC.sortSumOfSquares(sc);

  ASSERT_NEAR(4149.44, ShapeInfo->at(5)->sumOfSquares(), 0.01);
  ASSERT_NEAR(511.882, ShapeInfo->at(4)->sumOfSquares(), 0.001);
  ASSERT_NEAR(292.836, ShapeInfo->at(3)->sumOfSquares(), 0.001);
  ASSERT_NEAR(145.222, ShapeInfo->at(2)->sumOfSquares(), 0.001);
  ASSERT_NEAR(142.534, ShapeInfo->at(1)->sumOfSquares(), 0.001);
  ASSERT_NEAR(11.9069, ShapeInfo->at(0)->sumOfSquares(), 0.001);
}
TEST(SumOfSquaresAscendingLambda,sumOfSquaresSort)
{
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort SA(ShapeInfo);
  SA.sortSumOfSquares([](Shape *x,Shape *y){
    return x->sumOfSquares() < y->sumOfSquares();
  });//[]Function
  ASSERT_NEAR(4149.44, ShapeInfo->at(5)->sumOfSquares(), 0.01);
  ASSERT_NEAR(511.882, ShapeInfo->at(4)->sumOfSquares(), 0.001);
  ASSERT_NEAR(292.836, ShapeInfo->at(3)->sumOfSquares(), 0.001);
  ASSERT_NEAR(145.222, ShapeInfo->at(2)->sumOfSquares(), 0.001);
  ASSERT_NEAR(142.534, ShapeInfo->at(1)->sumOfSquares(), 0.001);
  ASSERT_NEAR(11.9069, ShapeInfo->at(0)->sumOfSquares(), 0.001);
}
TEST(SumOfSquaresDescendingLambda,sumOfSquaresSort)
{
  //Function QuickSortTest
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort SD(ShapeInfo);
  SD.sortSumOfSquares([](Shape *x,Shape *y){
    return x->sumOfSquares() > y->sumOfSquares();
  });//[]Function
  ASSERT_NEAR(4149.44, ShapeInfo->at(0)->sumOfSquares(), 0.01);
  ASSERT_NEAR(511.882, ShapeInfo->at(1)->sumOfSquares(), 0.001);
  ASSERT_NEAR(292.836, ShapeInfo->at(2)->sumOfSquares(), 0.001);
  ASSERT_NEAR(145.222, ShapeInfo->at(3)->sumOfSquares(), 0.001);
  ASSERT_NEAR(142.534, ShapeInfo->at(4)->sumOfSquares(), 0.001);
  ASSERT_NEAR(11.9069, ShapeInfo->at(5)->sumOfSquares(), 0.001);
}
TEST(QuickSortClass, quickSort)
{
  //Object QuickSortTest
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
  for (int i=0; i<6; i++)
  {
    ShapeInfo->push_back(test_array[i]);
  }
  Sort Q(ShapeInfo);
  AscendingComparison qaq("area"); //Object
  Q.quickSort(qaq);
  ASSERT_NEAR(0.5, ShapeInfo->at(0)->area(), 0.001);
  ASSERT_NEAR(3.5, ShapeInfo->at(1)->area(), 0.001);
  ASSERT_NEAR(2*3.14159, ShapeInfo->at(2)->area(), 0.001);
  ASSERT_NEAR(3*3.14159, ShapeInfo->at(3)->area(), 0.001);
  ASSERT_NEAR(5*3.14159, ShapeInfo->at(4)->area(), 0.001);
  ASSERT_NEAR(18*3.14159, ShapeInfo->at(5)->area(), 0.001);
}
TEST(QuickSortFunction,quickSort)
{
  //Function QuickSortTest
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
   for (int i=0; i<6; i++)
   {
     ShapeInfo->push_back(test_array[i]);
   }
  Sort SQ(ShapeInfo);
  SQ.quickSort(sumOfSquaresDescendingComparison);//Function
  ASSERT_NEAR(4149.44, ShapeInfo->at(0)->sumOfSquares(), 0.01);
  ASSERT_NEAR(511.882, ShapeInfo->at(1)->sumOfSquares(), 0.001);
  ASSERT_NEAR(292.836, ShapeInfo->at(2)->sumOfSquares(), 0.001);
  ASSERT_NEAR(145.222, ShapeInfo->at(3)->sumOfSquares(), 0.001);
  ASSERT_NEAR(142.534, ShapeInfo->at(4)->sumOfSquares(), 0.001);
  ASSERT_NEAR(11.9069, ShapeInfo->at(5)->sumOfSquares(), 0.001);
}
TEST(QuickSortLambda,quickSort)
{
  //Lambda QuickSortTest
  Shape* test_array[6] = {new CircularSector(5,72), new CircularSector(2,180), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Ellipse(6,3), new Triangle(0,0,1,0,0,1)};
  vector<Shape*>* ShapeInfo = new vector<Shape*>;
   for (int i=0; i<6; i++)
   {
     ShapeInfo->push_back(test_array[i]);
   }
  Sort SQL(ShapeInfo);
  SQL.quickSort([](Shape* x,Shape* y)
  {
    return x->perimeter() < y->perimeter();
  });//Lambda
  ASSERT_NEAR(30.849, ShapeInfo->at(5)->perimeter(), 0.001);
  ASSERT_NEAR(16.283, ShapeInfo->at(4)->perimeter(), 0.001);
  ASSERT_NEAR(14.283, ShapeInfo->at(3)->perimeter(), 0.001);
  ASSERT_NEAR(11.414, ShapeInfo->at(2)->perimeter(), 0.001);
  ASSERT_NEAR(10.283, ShapeInfo->at(1)->perimeter(), 0.001);
  ASSERT_NEAR(3.414, ShapeInfo->at(0)->perimeter(), 0.001);
}

#endif
