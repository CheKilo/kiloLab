#include "kilo/function.hpp"
#include "gtest/gtest.h"

#include <sstream>
#include <iostream>

// 测试 kilo::function 是否能正确存储和调用无参数无返回值的 lambda 函数
TEST(FunctionTest, CanStoreAndCallVoidLambda) {
    std::ostringstream oss;
    auto original_cout = std::cout.rdbuf(oss.rdbuf());

    kilo::function<void()> myfun([](){ std::cout << "Hello World!" << std::endl; });
    myfun();

    std::cout.rdbuf(original_cout);

    EXPECT_EQ(oss.str(), "Hello World!\n");
}

// 测试 kilo::function 是否能正确存储和调用有参数有返回值的 lambda 函数
TEST(FunctionTest, CanStoreAndCallParameterizedLambda) {
    kilo::function<int(int)> addOne([](int x) { return x + 1; });
    int result = addOne(5);
    EXPECT_EQ(result, 6);
}

// 测试 kilo::function 的拷贝构造函数
TEST(FunctionTest, CopyConstructorWorks) {
    kilo::function<int(int)> addOne([](int x) { return x + 1; });
    kilo::function<int(int)> addOneCopy(addOne);
    int result = addOneCopy(5);
    EXPECT_EQ(result, 6);
}

// 测试 kilo::function 的赋值运算符
TEST(FunctionTest, AssignmentOperatorWorks) {
    kilo::function<int(int)> addOne([](int x) { return x + 1; });
    kilo::function<int(int)> addOneAssigned;
    addOneAssigned = addOne;
    int result = addOneAssigned(5);
    EXPECT_EQ(result, 6);
}