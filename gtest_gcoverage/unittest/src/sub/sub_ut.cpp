#include <gtest/gtest.h>
#include "sub/sub.h"
namespcae {
TEST(subTest, null)
{
    Sub sub_tmp;
    EXPECT_EQ(2, sub_tmp.sub(1, 1));
}
TEST(printTest, null)
{
    Sub sub_tmp;
    sub_tmp.print();
}
}
