#include <gtest/gtest.h>
#include <sys/stat.h>
#include "../src/iterator.h"
#include "../src/element.h"
#include "../src/integer.h"
#include "../src/set.h"

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ElementTest, integerTest) {
    Element * element;    
    Integer integer=Integer(1);

    //(1)
    ASSERT_EQ(integer.value(),1);
    //(2)
    try{
        integer.add(element);
    }
    catch(string s){
        ASSERT_EQ("It's an integer!",s);
    }
    //(3)
    ASSERT_EQ(1,integer.size());
    //(4)
    ASSERT_EQ("1",integer.toString());
    //(5)
    try{
        Iterator * it = integer.createIterator();
        it->first(); // Initialize
    }
    catch(string s){
        ASSERT_EQ(s,"No child member!");
    }
    //(6)
    try{
        integer.setOperator('a');
    }
    catch(string s){
        ASSERT_EQ(s,"Cannot set operator on it!");
    }
    //(7)
    //problem 4 and 5
}
TEST(ElementTest, setTest) {
    Integer integer(1);
    Integer integer2(1);        
    Set set=Set();
    //(2)
    set.add(&integer);
    set.add(&integer2);
    ASSERT_EQ("{1}",set.toString());
    //(3)
    ASSERT_EQ(set.size(),2);
    //(6)
    try{
        set.setOperator('.');
    }
    catch(string err){
        ASSERT_EQ(err,"Invalid operator!");
    }

}