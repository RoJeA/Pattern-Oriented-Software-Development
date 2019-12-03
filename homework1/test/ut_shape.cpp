#include<gtest/gtest.h>
#include"../src/shape.h"
#include"../src/circular_sector.h"
#include"../src/ellipse.h"
#include"../src/triangle.h"
#include<algorithm>

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST (ShapeTest, first)
{
  ASSERT_TRUE(true);
}

TEST (ShapeTest, CircularSector)
{
  CircularSector c(10,90);
  ASSERT_NEAR(78.53975, c.area(), 0.001);
  ASSERT_NEAR(35.70795, c.perimeter(), 0.001);
}

TEST (ShapeTest, Ellipse)
{
  Ellipse s(5, 2);
  ASSERT_NEAR(31.4159, s.area(), 0.001); //S=pi*a*b
  ASSERT_NEAR(24.566, s.perimeter(), 0.001); //L=2*pi*b+4*(a-b)
}

TEST (ShapeTest, Triangle)
{
  Triangle r(0, 0, 1, 1, 2, 0);
  ASSERT_NEAR(1, r.area(), 0.001);
  ASSERT_NEAR(4.828, r.perimeter(), 0.001);
}

//TEST(ShapeTest, Sorting)
//{
//  Shape* test_array[6] = {new CircularSector(2,180), new CircularSector(5,72), new Ellipse(6,3), new Ellipse(3,1), new Triangle(-1,3,0,4,3,0), new Triangle(0,0,1,0,0,1)};
                          //2*pi                       //5*pi                   //18*pi             //3*pi            //3.5   //-1              //0.5
//  std::sort(test_array, test_array+6, [](Shape * a, Shape *b)
//  {
//    return a->area() < b->area();
//  });
//  ASSERT_NEAR(0.5, test_array[0]->area(), 0.001);
//  ASSERT_NEAR(3.5, test_array[1]->area(), 0.001);
//  ASSERT_NEAR(2*3.14159, test_array[2]->area(), 0.001);
//  ASSERT_NEAR(3*3.14159, test_array[3]->area(), 0.001);
//  ASSERT_NEAR(5*3.14159, test_array[4]->area(), 0.001);
//  ASSERT_NEAR(18*3.14159, test_array[5]->area(), 0.001);
//}
