#include <gtest/gtest.h>
#include <math.h>
#include "./../src/complex_solids.h"
#include "./../src/cone.h"
#include "./../src/solid.h"
#include "./../src/square_cylinder.h"
#include "./../src/triangular_pyramid.h"


TEST (SolidTest, TriangularPyramidCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of TriangularPyramid
  TriangularPyramid tt(0,1,0,-1,1,0,1);
  ASSERT_NEAR(1,tt.bottomArea(),0.01);
  ASSERT_NEAR(0.333333,tt.volume(),0.01);
}

TEST (SolidTest, ConeCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of Cone
  Cone ca(0,0,1,0,1);
  ASSERT_NEAR(3.14159, ca.bottomArea(), 0.1);
  Cone cv(0,0,1,0,3);
  ASSERT_NEAR(3.14159,cv.volume(),0.1);

  try{
    Cone c_Ex(0,0,0,0,4);
    ASSERT_EQ(true,false);
  }
  catch(string s){
    ASSERT_EQ("Bottom is not a Circle!",s);
  }
}

TEST (SolidTest, SquareCylinderCaculate)
{
  // 2 points
  // Test bottomArea() and volume() of SquareCylinder
  SquareCylinder s(5,5);
  ASSERT_EQ(25,s.bottomArea());
  ASSERT_EQ(125,s.volume());
}

TEST (SolidTest, ComplexSolidsTest)
{
  // 2 points
  //Test numberOfChild of ComplexSolids
  SquareCylinder sc(5,5);
  Cone c1(0,0,1,0,3);
  Cone c2(0,0,1,0,1);
  TriangularPyramid tp(0,1,0,-1,1,0,1);
  vector<Solid*>* SolidInfo;
  SolidInfo->add(sc);
  SolidInfo->add(c1);
  SolidInfo->add(c2);
  SolidInfo->add(tp);
  ASSERT_EQ(4,ComplexSolids(SolidInfo).numberOfChild());
}

TEST (SolidTest, ComplexSolidsCalculate)
{
  // 2 points
  // Test bottomArea() and volume() of ComplexSolids
}


// TEST (SolidTest, findBySolid){
//   // 5 points
//   // Test find() method of cone and TriangularPyramid and SquareCylinder
// }
//
// TEST (SolidTest, findByComplextSolids){
//   // 5 points
//   // Test find() method of ComplexSolids
// }
