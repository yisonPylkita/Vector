#include <iostream>
#include "Vector.hpp"
#include <vector>
using namespace std;

int main()
{
    Vector<int> x(15, 5);
    Vector<int> y(20, 10);
    Vector<int> z = Vector<int>(5, 35);

    Vector<int>::iterator iter;
    Vector<int>::iterator iter2;

    if (x != y)
        std::cout << "x not the same as y" << std::endl;

    iter = x.begin();
    iter2 = y.begin();

    x.push_back(15);
    x.push_back(6);
    x.push_back(3);

    for (auto &a: x)
        std::cout << " " << a << " ";
    std::cout << std::endl;

    cout    << "Hello World! " << *iter
            << " " << x.capacity() << " "
            << " " << x.max_size() << " "
            << " " << std::boolalpha << x.empty() << " "
            << " " << x.front() << " "
            << " " << x.back() << " "
         << endl;

    return 0;
}

