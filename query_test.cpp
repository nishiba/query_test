#include "stdafx.h"
#include "gtest/gtest.h"
#include "query/query.h"

TEST(Query, skipTest)
{
    const std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    const std::vector<int> y = query(x).skip(2).toStdVector();
    EXPECT_EQ(x[2], y[0]);
}

TEST(Query, takeTest)
{
    const std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    const std::vector<int> y = query(x).take(2).toStdVector();
    EXPECT_EQ(2, y.size());
    EXPECT_EQ(x[1], y[1]);
}

TEST(Query, zipTest)
{
    const std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    const std::vector<int> y = { 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10 };
    const auto z = zip(x, y).toStdVector();
    EXPECT_EQ(x[0], z[0].get<0>());
    EXPECT_EQ(y[0], z[0].get<1>());
}


TEST(Query, selectTest)
{
    const std::vector<int> x = {0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9};
    auto f = [](auto& a) {return a + 1; };
    const std::vector<int> y = query(x).select(f).toStdVector();
    EXPECT_EQ(y[0], f(x[0]));
    EXPECT_EQ(y[3], f(x[3]));
}

TEST(Query, selectWithIndexTest)
{
    const std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    auto f = [](const int& a, std::size_t i) {return a + 1; };
    const std::vector<int> y = query(x).selectWithIndex(f).toStdVector();
    EXPECT_EQ(f(x[0], 0), y[0]);
    EXPECT_EQ(f(x[2], 2), y[2]);
}

TEST(Query, selectUnzipTest)
{
    const std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    const std::vector<int> y = { 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 0 };
    const std::vector<int> z = zip(x, y)
        .selectUnzip([](int a, int b) {return a + b; })
        .toStdVector();
    EXPECT_EQ(x[0] + y[0], z[0]);
    EXPECT_EQ(x[1] + y[1], z[1]);
}


TEST(Query, applyTest)
{
    std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    auto f = [](auto& a) {a += 1; };
    query(x).apply(f);
    EXPECT_EQ(1, x[0]);
    EXPECT_EQ(4, x[3]);
}

TEST(Query, applyWithIndexTest)
{
    std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    auto f = [](auto& a, std::size_t i) {a += i; };
    query(x).applyWithIndex(f);
    EXPECT_EQ(0, x[0]);
    EXPECT_EQ(6, x[3]);
}

TEST(Query, applyUnzipTest)
{
    std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    std::vector<int> y = { 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 0 };
    zip(x, y).applyUnzip([](int& a, int& b) { a += 1; b += 1; });
    EXPECT_EQ(2, x[1]);
    EXPECT_EQ(3, y[1]);
}


TEST(Query, combinationTest)
{
    std::vector<int> x = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9 };
    std::vector<int> y 
        = query(x).skip(1).take(3)
        .select([](int a) {return a + 1; })
        .toStdVector();
    EXPECT_EQ(2, y[0]);
    EXPECT_EQ(4, y[2]);
}


