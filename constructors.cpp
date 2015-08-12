#include "Vector.hpp"
#include "catch.hpp"


TEST_CASE("constructor 1 test", "[constructor][1]")
{
    Vector<int> vec;

    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() >= 0);
}

TEST_CASE("constructor 2 test", "[constructor][2]")
{
    Vector<int> vec(10, 5);

    REQUIRE(vec.size() == 10);
    REQUIRE(vec.capacity() >= 10);

    for (auto x : vec) {
        REQUIRE(x == 5);
    }
}

TEST_CASE("constructor 3 test", "[constructor][3]")
{
    Vector<int> vec(5);

    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() >= 5);
}

TEST_CASE("constructor 6 test", "[constructor][6]")
{
    Vector<int> vec(10, 5);

    unsigned vecSize = vec.size();           REQUIRE(vecSize == 10);
    unsigned vecCapacity = vec.capacity();   REQUIRE(vecCapacity >= 10);
    int *vecData = new int[vecSize];

    for (unsigned i = 0; i < vec.size(); ++i)
        vecData[i] = vec[i];


    Vector<int> vec2(std::move(vec));

    REQUIRE(vec.size() == 0);
    REQUIRE(vec.capacity() == 0);

    REQUIRE(vec2.size() == vecSize);
    REQUIRE(vec2.capacity() >= vecCapacity);

    for (unsigned i = 0; i < vec2.size(); ++i)
        REQUIRE(vecData[i] == vec2[i]);
}