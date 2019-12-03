#ifndef UT_SORT_H
#define UT_SORT_H

#include<gtest/gtest.h>
#include"../src/shape.h"
#include"../src/circular_sector.h"
#include"../src/ellipse.h"
#include"../src/triangle.h"
#include"../src/sort.h"
#include"../src/terminal.h"
#include<algorithm>

// //First Test
TEST(HelloTest,First)
{
  ASSERT_EQ("Hi,First Test","Hi,First Test");
}

TEST(TerminalTest,AreaDescending)
{
  Terminal * test = new Terminal("Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area dec");
  ASSERT_EQ("[12.000000, 6.000000]" , test->showResult());
}
TEST(TerminalTest_RegEx,AreaAscending)
{
  Terminal * test = new Terminal("angle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area inc");
  ASSERT_EQ("[12.000000]" , test->showResult());
}
TEST(SpecialCase_ElementCount,AreaAscending)
{
  Terminal * test = new Terminal("Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) Triangle (0,0,3,2,0) area inc");
  ASSERT_EQ("[6.000000, 12.000000]" , test->showResult());
}
TEST(SpecialCase_StrangeAlphaNum,AreaAscending)
{
  Terminal * test = new Terminal("fgfhyTriangle (-2,0,0,3,2,0) 1264Triangle (-2,0,0,6,2,0) area inc");
  ASSERT_EQ("[]" , test->showResult());
}
TEST(SpecialCase_SpaceStrangeAlphaNum,AreaDescending)
{
  Terminal * test = new Terminal("123 Triangle (-2,0,0,3,2,0) Triangle (-2,0,0,6,2,0) area dec");
  ASSERT_EQ("[12.000000, 6.000000]" , test->showResult());
}
TEST(SpecialCase_StrangeSymbol,PerimeterAscending)
{
  Terminal * test = new Terminal("CircularSector (2,180) Triangle@ (-2,0,0,6,2,0) perimeter inc");
  ASSERT_EQ("[10.283185]" , test->showResult());
}
TEST(SpecialCase_SpaceStrangeSymbol,PerimeterDescending)
{
  Terminal * test = new Terminal("CircularSector (2,180)  Triangle (-2,0,0,6,2,0) @*/+- perimeter dec ");
  ASSERT_EQ("[16.649111, 10.283185]" , test->showResult());
}

TEST(Unuseful_User_Input , Exception)
{
  Terminal * test = new Terminal("CircularSector (2,180)  Triangle (-2,0,0,6,2,0) perimeter");
  try{
    test->showResult();
  }
  catch(string error){
    // cout << "error : "<< error <<endl;
    ASSERT_EQ("Unuseful User Input!" , error);
  }
}
#endif
