#include <iostream>

#include "BitArray.cpp"

int main()
{
    BitArray a(7, 0b1000111);
    std::cout << a.to_string() << std::endl;

    a <<= 9;
    std::cout << a.to_string() << std::endl;
    return 0;
}