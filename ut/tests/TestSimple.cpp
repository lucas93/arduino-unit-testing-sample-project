#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <BaseClass.h>
#include <LastClass.h>


// Simple test, does not use gmock
TEST(Dummy, foobar)
{
    EXPECT_EQ(1, 1);
}


// Real class we want to mock


// Mock class
class MockTeaBreak : public TeaBreak
{
public:
    MOCK_METHOD2(makeCoffee,    int(bool milk, double sugars));
    MOCK_METHOD0(makeHerbalTea, int());
};


using ::testing::Return;
using ::testing::_;

// Mocked test
TEST(TeaBreakTest, MorningTea)
{
    auto i = 1;
    MockTeaBreak  teaBreak;
    EXPECT_CALL(teaBreak, makeCoffee(_,_))
        .WillOnce(Return(i+1))
        .WillOnce(Return(i));
    EXPECT_CALL(teaBreak, makeHerbalTea())
        .WillOnce(Return(3));

    EXPECT_LE(teaBreak.morningTea(), 6);
}
