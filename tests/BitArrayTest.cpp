#include "BitArray.hpp"
#include <gtest/gtest.h>

TEST(ConstructorTest, initialization)
{
    BitArray a(70, ALL_ONE);
    BitArray b(5, 0xAC00000000000000);
    // 1010110000000000000000000000000000000000000000000000000000000000

    EXPECT_EQ(a.size(), 70);
    EXPECT_EQ(b.size(), 5);

    EXPECT_TRUE(a[60]);
    EXPECT_TRUE(a[0]);
    EXPECT_FALSE(a[64]);

    EXPECT_FALSE(b[1]);
    EXPECT_TRUE(b[0]);
    try
    {
        EXPECT_EQ(a[70], 0);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }

    BitArray c(a);
    EXPECT_EQ(c.size(), 70);
    EXPECT_EQ(c[63], 1);
}

TEST(ConstructorTest, NegativeInitialization)
{
    EXPECT_THROW(BitArray b(-5), std::invalid_argument);
}

TEST(ConstructorTest, ZeroInitialization)
{
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(FirstMethodsTest, Testing)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray b(5, 0xA800000000000000); // 0b10101

    a.swap(b);

    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(a.size(), 5);

    EXPECT_TRUE(a[0]);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[2], 1);

    EXPECT_TRUE(b[0]);
    EXPECT_EQ(b[4], 0);
    EXPECT_EQ(b[2], 1);

    BitArray c;
    c = a;

    EXPECT_TRUE(c[0]);
    EXPECT_EQ(c[1], 0);
    EXPECT_EQ(c[2], 1);

    a.resize(15, true);
    EXPECT_EQ(a.size(), 15);

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[4], 1); // a = 0b101011111111

    EXPECT_EQ(a[5], 1);
    EXPECT_EQ(a[14], 1);

    try
    {
        EXPECT_EQ(a[15], 1);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }

    a.clear();
    EXPECT_EQ(a.empty(), true);

    try
    {
        EXPECT_EQ(a[70], 0);
    }
    catch (const std::range_error &e)
    {
        std::cerr << e.what();
    }

    b.push_back(true); // 0b1010010101
    EXPECT_EQ(b[9], 1);
    b.push_back(false); // 0b10100101010
    EXPECT_EQ(b[10], 0);
}

TEST(OperatorsTest, BitArrayOperators)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111

    std::cout << "-------------------------------" << std::endl;
    std::cout << a.to_string() << std::endl;
    std::cout << b.to_string() << std::endl;
    std::cout << "-------------------------------" << std::endl;

    EXPECT_EQ((a & b).to_string(), "00101");
    EXPECT_EQ((a | b).to_string(), "11111");
    EXPECT_EQ((a ^ b).to_string(), "11010");

    BitArray c(6, 0x7800000000000000); // 0b011110

    try
    {
        a & c;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what();
    }

    a >>= 3;
    b <<= 3;

    EXPECT_EQ(a.to_string(), "00010");
    EXPECT_EQ(b.to_string(), "11000");

    BitArray d(70, 0xA800000000000000); // 0b10101..0

    std::cout << "-------------------------------" << std::endl;
    std::cout << d.to_string() << std::endl;
    std::cout << "-------------------------------" << std::endl;

    EXPECT_EQ((d >> 64).to_string(), "0000000000000000000000000000000000000000000000000000000000000000101010");

    d = ~d;

    EXPECT_EQ(d.to_string(), "0101011111111111111111111111111111111111111111111111111111111111111111");
}

TEST(SecondMethodsTest, Testing)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray b(5, 0xA800000000000000); // 0b10101

    a.set(0, false);
    EXPECT_EQ(a.to_string(), "001001010");
    a.set();
    EXPECT_EQ(a.to_string(), "111111111");
    a.reset(2);
    EXPECT_EQ(a.to_string(), "110111111");
    a.reset();
    EXPECT_EQ(a.to_string(), "000000000");

    EXPECT_EQ(b.any(), true);
    EXPECT_EQ(a.none(), true);

    EXPECT_EQ(b.count(), 3);

    EXPECT_EQ(b.size(), 5);
}
