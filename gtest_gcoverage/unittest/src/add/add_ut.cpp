#include <gtest/gtest.h>
#include "add/add.h"
namespcae {
TEST(addTest, null)
{
    Add add_tmp;
    EXPECT_EQ(2, add_tmp.add(1, 1));
}
TEST(printTest, null)
{
    Add add_tmp;
    add_tmp.print();
}
}
