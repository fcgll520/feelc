#include <gtest/gtest.h>
#include "common_ut.h"
#include "add/add.h"
//namespcae {
TEST(addTest, null)
{
    Add add_tmp;
    EXPECT_EQ(2, add_tmp.add(1, 1));
}
TEST(AddPrintTest, null)
{
    Add add_tmp;
    add_tmp.print();
}
//}
