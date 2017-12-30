#include <gtest/gtest.h>
#include "common_ut.h"
#include "sub/sub.h"
//namespcae {
TEST(subTest, null)
{
    Sub sub_tmp;
    EXPECT_EQ(0, sub_tmp.sub(1, 1));
}
TEST(SubPrintTest, null)
{
    Sub sub_tmp;
    sub_tmp.print();
}
//}
