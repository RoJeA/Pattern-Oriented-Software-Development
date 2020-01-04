#include <gtest/gtest.h>
#include "ut_fs.h"
#include "ut_file.h"
#include "ut_filesystem.h"
int main(int argc, char ** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
