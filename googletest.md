**googletest 定義的斷言（ Assert ）**

*  基本斷言二進位制比較 字串比較

1.  condition為真 
```
ASSERT_TRUE(condition);
EXPECT_TRUE(condition);
```
2.  condition為假ASSERT_EQ(expected,actual);
```
ASSERT_FALSE(condition);
EXPECT_FALSE(condition);
```
3.  expected==actual
`EXPECT_EQ(expected,actual);`
4.  val1!=val2
`ASSERT_NE(val1,val2);`
`EXPECT_NE(val1,val2);`
5.  val1<val2
```
ASSERT_LT(val1,val2);
EXPECT_LT(val1,val2);
```
6.  val1<=val2
```
ASSERT_LE(val1,val2);
EXPECT_LE(val1,val2);
```

7.  val1>val2
```
ASSERT_GT(val1,val2);
EXPECT_GT(val1,val2);
```
8.  val1>=val2
```
ASSERT_GE(val1,val2);
EXPECT_GE(val1,val2);
```
9.  兩個 C 字串有相同的內容
`ASSERT_STREQ(expected_str,actual_str);`
`EXPECT_STREQ(expected_str,actual_str);`
10.  兩個 C 字串有不同的內容
`ASSERT_STRNE(str1,str2);`
`EXPECT_STRNE(str1,str2);`
11.  兩個 C 字串有相同的內容，忽略大小寫
`ASSERT_STRCASEEQ(expected_str,actual_str);`
`EXPECT_STRCASEEQ(expected_str,actual_str);`
12.  兩個 C 字串有不同的內容，忽略大小寫
`ASSERT_STRCASENE(str1,str2);`
`EXPECT_STRCASENE(str1,str2);`


*  在執行可執行目標程式時，可以使用 --gtest_filter 來指定要執行的測試用例，如：

1. `./foo_test` 沒有指定 filter ，執行所有測試；
2. `./foo_test --gtest_filter=*` 指定 filter 為 * ，執行所有測試；
3. `./foo_test --gtest_filter=FooTest.*` 執行測試用例 FooTest 的所有測試；
4. `./foo_test --gtest_filter=*Null*:*Constructor*` 執行所有全名（即測試用例名 + “ . ” + 測試名，如 GlobalConfigurationTest.noConfigureFileTest ）含有"Null" 或 "Constructor" 的測試；
5. `./foo_test --gtest_filter=FooTest.*-FooTest.Bar` 執行測試用例 FooTest 的所有測試，但不包括 FooTest.Bar。


定義韌體類的方法為：

寫一個繼承自::testing::Test的類，為使該類的子類能訪問到該類的資料，使用public或protected作為訪問控制標識；
在該類中，定義測試例項將用到的資料；
使用SetUp()方法或預設建構函式作資料初始化操作，使用TearDown()方法或解構函式作資料清理操作，注意SetUp()和TearDown()的拼寫；
如有需要，還可以在該類中定義成員函式，正如初始化資料，這裡所定義的成員函式也可被測試例項重複使用

**Simple Tests**
To create a test:

Use the `TEST()` macro to define and name a test function. These are ordinary C++ functions that don't return a value.
In this function, along with any valid C++ statements you want to include, use the various googletest assertions to check values.
The test's result is determined by the assertions; if any assertion in the test fails (either fatally or non-fatally), or if the test crashes, the entire test fails. Otherwise, it succeeds.
```
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```

`TEST()` arguments go from general to specific. The first argument is the name of the test suite, and the second argument is the test's name within the test case. Both names must be valid C++ identifiers, and they should not contain any underscores (_). A test's full name consists of its containing test suite and its individual name. Tests from different test suites can have the same individual name.

For example, let's take a simple integer function:

`int Factorial(int n);  // Returns the factorial of n`
A test suite for this function might look like:

```
// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(Factorial(1), 1);
  EXPECT_EQ(Factorial(2), 2);
  EXPECT_EQ(Factorial(3), 6);
  EXPECT_EQ(Factorial(8), 40320);
}
```

googletest groups the test results by test suites, so logically related tests should be in the same test suite; in other words, the first argument to their TEST() should be the same. In the above example, we have two tests, HandlesZeroInput and HandlesPositiveInput, that belong to the same test suite FactorialTest.

When naming your test suites and tests, you should follow the same convention as for naming functions and classes.

Availability: Linux, Windows, Mac.

**Test Fixtures: Using the Same Data Configuration for Multiple Tests {#same-data-multiple-tests}**
If you find yourself writing two or more tests that operate on similar data, you can use a test fixture. This allows you to reuse the same configuration of objects for several different tests.

To create a fixture:

1. Derive a class from `::testing::Test` . Start its body with protected:, as we'll want to access fixture members from sub-classes.
2. Inside the class, declare any objects you plan to use.
3. If necessary, write a default constructor or `SetUp()` function to prepare the objects for each test. A common mistake is to spell `SetUp()` as `Setup()` with a small `u` - Use override in C++11 to make sure you spelled it correctly.
4. If necessary, write a destructor or `TearDown()` function to release any resources you allocated in `SetUp()` . To learn when you should use the constructor/destructor and when you should use `SetUp()`/`TearDown()`, read the FAQ.
5. If needed, define subroutines for your tests to share.

When using a fixture, use `TEST_F()` instead of `TEST()` as it allows you to access objects and subroutines in the test fixture:

```
TEST_F(TestFixtureName, TestName) {
  ... test body ...
}
```

**Like `TEST()`, the first argument is the test suite name, but for `TEST_F()` this must be the name of the test fixture class. You've probably guessed: _F is for fixture.**

Unfortunately, the C++ macro system does not allow us to create a single macro that can handle both types of tests. Using the wrong macro causes a compiler error.

Also, you must first define a test fixture class before using it in a `TEST_F()`, or you'll get the compiler error "virtual outside class declaration".

For each test defined with  `TEST_F()`, googletest will create a fresh test fixture at runtime, immediately initialize it via `SetUp()`, run the test, clean up by calling `TearDown()`, and then delete the test fixture. Note that different tests in the same test suite have different test fixture objects, and googletest always deletes a test fixture before it creates the next one. googletest does not reuse the same test fixture for multiple tests. Any changes one test makes to the fixture do not affect other tests.

As an example, let's write tests for a FIFO queue class named Queue, which has the following interface:

```
template <typename E>  // E is the element type.
class Queue {
 public:
  Queue();
  void Enqueue(const E& element);
  E* Dequeue();  // Returns NULL if the queue is empty.
  size_t size() const;
  ...
};
````

First, define a fixture class. By convention, you should give it the name FooTest where Foo is the class being tested.

````
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};
````

In this case, `TearDown()` is not needed since we don't have to clean up after each test, other than what's already done by the destructor.

Now we'll write tests using `TEST_F()` and this fixture.

````
TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
  int* n = q0_.Dequeue();
  EXPECT_EQ(n, nullptr);

  n = q1_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 1);
  EXPECT_EQ(q1_.size(), 0);
  delete n;

  n = q2_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 2);
  EXPECT_EQ(q2_.size(), 1);
  delete n;
}
````

The above uses both` ASSERT_*` and` EXPECT_*` assertions. The rule of thumb is to use `EXPECT_*` when you want the test to continue to reveal more errors after the assertion failure, and use `ASSERT_*` when continuing after failure doesn't make sense. For example, the second assertion in the `Dequeue` test is `ASSERT_NE(nullptr, n)`, as we need to dereference the pointer `n` later, which would lead to a segfault when `n` is `NULL`.

When these tests run, the following happens:

1. googletest constructs a QueueTest object (let's call it t1).
2. t1.SetUp() initializes t1.
3. The first test (IsEmptyInitially) runs on t1.
4. t1.TearDown() cleans up after the test finishes.
5. t1 is destructed.
6. The above steps are repeated on another QueueTest object, this time running the DequeueWorks test.

Availability: Linux, Windows, Mac.

**Invoking the Tests**
`TEST() `and `TEST_F() `implicitly register their tests with googletest. So, unlike with many other C++ testing frameworks, you don't have to re-list all your defined tests in order to run them.

After defining your tests, you can run them with RUN_ALL_TESTS(), which returns 0 if all the tests are successful, or 1 otherwise. Note that RUN_ALL_TESTS() runs all tests in your link unit--they can be from different test suites, or even different source files.

When invoked, the `RUN_ALL_TESTS()` macro:

  * Saves the state of all googletest flags.
  * Creates a test fixture object for the first test.
  * Initializes it via SetUp().
  * Runs the test on the fixture object.
  * Cleans up the fixture via TearDown().
  * Deletes the fixture.
  * Restores the state of all googletest flags.
  * Repeats the above steps for the next test, until all tests have run.
  * If a fatal failure happens the subsequent steps will be skipped.


> IMPORTANT: You must not ignore the return value of RUN_ALL_TESTS(), or you will get a compiler error. The rationale for this design is that the automated testing service determines whether a test has passed based on its exit code, not on its stdout/stderr output; thus your main() function must return the value of RUN_ALL_TESTS().
> 
> Also, you should call RUN_ALL_TESTS() only once. Calling it more than once conflicts with some advanced googletest features (e.g., thread-safe death tests) and thus is not supported.

**Availability:** Linux, Windows, Mac.

**Writing the main() Function**
Write your own main() function, which should return the value of RUN_ALL_TESTS().

You can start from this boilerplate:


```
#include "this/package/foo.h"
#include "gtest/gtest.h"

namespace {

// The fixture for testing class Foo.
class FooTest : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  FooTest() {
     // You can do set-up work for each test here.
  }

  ~FooTest() override {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Objects declared here can be used by all tests in the test suite for Foo.
};

// Tests that the Foo::Bar() method does Abc.
TEST_F(FooTest, MethodBarDoesAbc) {
  const std::string input_filepath = "this/package/testdata/myinputfile.dat";
  const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
  Foo f;
  EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
}

// Tests that Foo does Xyz.
TEST_F(FooTest, DoesXyz) {
  // Exercises the Xyz feature of Foo.
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```


The `::testing::InitGoogleTest()` function parses the command line for googletest flags, and removes all recognized flags. This allows the user to control a test program's behavior via various flags, which we'll cover in the AdvancedGuide. You must call this function before calling RUN_ALL_TESTS(), or the flags won't be properly initialized.

On Windows, InitGoogleTest() also works with wide strings, so it can be used in programs compiled in UNICODE mode as well.

But maybe you think that writing all those main() functions is too much work? We agree with you completely, and that's why Google Test provides a basic implementation of main(). If it fits your needs, then just link your test with gtest_main library and you are good to go.

NOTE: `ParseGUnitFlags()` is deprecated in favor of `InitGoogleTest()`.

**Known Limitations**
Google Test is designed to be thread-safe. The implementation is thread-safe on systems where the pthreads library is available. It is currently unsafe to use Google Test assertions from two threads concurrently on other systems (e.g. Windows). In most tests this is not an issue as usually the assertions are done in the main thread. If you want to help, you can volunteer to implement the necessary synchronization primitives in gtest-port.h for your platform.