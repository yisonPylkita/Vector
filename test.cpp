#define CATCH_CONFIG_MAIN
#include "Vector.hpp"
#include "catch.hpp"


TEST_CASE("reserve test", "[reserve]")
{
    Vector<int> vec;
    vec.reserve(10);

    REQUIRE(vec.capacity() == 10);
}

TEST_CASE("push_back test - single velue", "[push_back][single value]")
{
    Vector<int> vec;
    vec.push_back(5);

    REQUIRE(vec[0] == 5);
}

TEST_CASE("begin test", "[begin]")
{
    Vector<int> vec(10, 5);

    REQUIRE(*(vec.begin()) == 5);
}

TEST_CASE("end test", "[end]")
{
    Vector<int> vec(10, 5);

    // end() points one element after Vector last element
    REQUIRE(*(vec.end() - sizeof(int)) == 5);
}

TEST_CASE("comparision test - size", "[comparision][size]")
{
    Vector<int> vec(15, 5);
    Vector<int> y(20, 5);

    REQUIRE(vec != y);
}

TEST_CASE("comparision test - value", "[comparision][value]")
{
    Vector<int> vec(20, 3);
    Vector<int> y(20, 5);

    REQUIRE(vec != y);
}
