#include "stdafx.h"
#include "gtest/gtest.h"
#include "query/query.h"

TEST(Query, skipTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    const std::vector<int> y = query(x).skip(2).toStdVector();
    EXPECT_EQ(x[2], y[0]);
}

TEST(Query, takeTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    const std::vector<int> y = query(x).take(2).toStdVector();
    EXPECT_EQ(2, y.size());
    EXPECT_EQ(x[1], y[1]);
}

TEST(Query, takeWhileTest)
{
    std::vector<int> x = range(1, 10).toStdVector();
    const std::vector<int> y = query(x).takeWhile([](int x) {return x < 3; }).toStdVector();
    EXPECT_EQ(2, y.size());
    EXPECT_EQ(x[1], y[1]);
}

TEST(Query, takeWhileWithIndexTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    const std::vector<int> y = query(x).takeWhileWithIndex([](int x, int i) {return i < 3; }).toStdVector();
    EXPECT_EQ(3, y.size());
    EXPECT_EQ(x[1], y[1]);
}


TEST(Query, zipTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    std::vector<int> y = range(1, 11).toStdVector();
    const auto z = zip(x, y).toStdVector();
    EXPECT_EQ(x[0], z[0].get<0>());
    EXPECT_EQ(y[0], z[0].get<1>());
}


TEST(Query, selectTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    auto f = [](auto& a) {return a + 1; };
    const std::vector<int> y = query(x).select(f).toStdVector();
    EXPECT_EQ(y[0], f(x[0]));
    EXPECT_EQ(y[3], f(x[3]));
}

TEST(Query, selectWithIndexTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    auto f = [](const int& a, std::size_t i) {return a + 1; };
    const std::vector<int> y = query(x).selectWithIndex(f).toStdVector();
    EXPECT_EQ(f(x[0], 0), y[0]);
    EXPECT_EQ(f(x[2], 2), y[2]);
}

TEST(Query, selectUnzipTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    std::vector<int> y = range(1, 11).toStdVector();
    const std::vector<int> z = zip(x, y)
        .selectUnzip([](int a, int b) {return a + b; })
        .toStdVector();
    EXPECT_EQ(x[0] + y[0], z[0]);
    EXPECT_EQ(x[1] + y[1], z[1]);
}



TEST(Query, applyTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    auto f = [](auto& a) {a += 1; };
    query(x).apply(f);
    EXPECT_EQ(1, x[0]);
    EXPECT_EQ(4, x[3]);
}

TEST(Query, applyWithIndexTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    auto f = [](auto& a, std::size_t i) {a += i; };
    query(x).applyWithIndex(f);
    EXPECT_EQ(0, x[0]);
    EXPECT_EQ(6, x[3]);
}

TEST(Query, applyUnzipTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    std::vector<int> y = range(1, 11).toStdVector();
    zip(x, y).applyUnzip([](int& a, int& b) { a += 1; b += 1; });
    EXPECT_EQ(2, x[1]);
    EXPECT_EQ(3, y[1]);
}

TEST(Query, RangeTest)
{
    std::vector<int> x = range(1, 10).toStdVector();
    EXPECT_EQ(9, x.size());
    EXPECT_EQ(2, x[1]);
    EXPECT_EQ(3, x[2]);
}

TEST(Query, AnyTest)
{
    EXPECT_EQ(true, range(1, 10).any([](int i) {return i == 2; }));
    EXPECT_EQ(false, range(1, 10).any([](int i) {return i == 12; }));
}

TEST(Query, AverageTest)
{
    auto x = range(1, 4);
    EXPECT_EQ(std::accumulate(x.begin(), x.end(), 0.0) / x.size(), x.average(0.0));
}

TEST(Query, SumTest)
{
    auto x = range(1, 4);
    EXPECT_EQ(std::accumulate(x.begin(), x.end(), 0.0) , x.sum(0.0));
}

TEST(Query, WhereTest)
{
    auto x = range(1, 4).where([](int a) {return a < 3; }).toStdVector();
    EXPECT_EQ(2, x.size());
}


TEST(Query, combinationTest)
{
    std::vector<int> x = range(0, 10).toStdVector();
    std::vector<int> y = query(x)
        .skip(1).take(3)
        .select([](int a) {return a + 1; })
        .toStdVector();
    EXPECT_EQ(2, y[0]);
    EXPECT_EQ(4, y[2]);
}


