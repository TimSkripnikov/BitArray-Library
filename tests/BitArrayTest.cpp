#include "BitArray.hpp"
#include <gtest/gtest.h>

TEST(BitArrayConstructorTest, ValidInitialization)
{
    BitArray a(70, ALL_ONE);
    BitArray b(5, 0xAC00000000000000); // 101011...

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
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    BitArray c(a);
    EXPECT_EQ(c.size(), 70);
    EXPECT_EQ(c[63], 1);
}

TEST(BitArrayConstructorTest, NegativeSizeThrows)
{
    EXPECT_THROW(BitArray b(-5), std::invalid_argument);
}

TEST(BitArrayConstructorTest, DefaultConstructor)
{
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayMethodsTest, Swap)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray b(5, 0xA800000000000000); // 0b10101

    std::cout << "Before swap:" << std::endl;
    std::cout << "a: " << a.to_string() << std::endl;
    std::cout << "b: " << b.to_string() << std::endl;

    a.swap(b);

    std::cout << "After swap:" << std::endl;
    std::cout << "a: " << a.to_string() << std::endl;
    std::cout << "b: " << b.to_string() << std::endl;

    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(a.size(), 5);
}

TEST(BitArrayMethodsTest, Resize)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    std::cout << "Before resize: " << a.to_string() << std::endl;

    a.resize(15, true);
    std::cout << "After resize: " << a.to_string() << std::endl;

    EXPECT_EQ(a.size(), 15);
    EXPECT_EQ(a[14], 1);
}

TEST(BitArrayMethodsTest, PushBack)
{
    BitArray b(5, 0xA800000000000000); // 0b10101

    b.push_back(true); // 0b101011
    std::cout << "After push_back(true): " << b.to_string() << std::endl;
    EXPECT_EQ(b[5], 1);

    b.push_back(false); // 0b1010110
    std::cout << "After push_back(false): " << b.to_string() << std::endl;
    EXPECT_EQ(b[6], 0);
}

TEST(BitArrayMethodsTest, Clear)
{
    BitArray a(10, 0xFFFF000000000000);
    std::cout << "Before clear: " << a.to_string() << std::endl;

    a.clear();
    std::cout << "After clear: " << a.to_string() << std::endl;

    EXPECT_TRUE(a.empty());
}

TEST(BitArrayOperatorsTest, ANDOperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111

    BitArray result = a & b;
    std::cout << "a & b: " << result.to_string() << std::endl;

    EXPECT_EQ(result.to_string(), "00101");
}

TEST(BitArrayOperatorsTest, OROperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111

    BitArray result = a | b;
    std::cout << "a | b: " << result.to_string() << std::endl;

    EXPECT_EQ(result.to_string(), "11111");
}

TEST(BitArrayOperatorsTest, XOROperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111

    BitArray result = a ^ b;
    std::cout << "a ^ b: " << result.to_string() << std::endl;

    EXPECT_EQ(result.to_string(), "11010");
}

TEST(BitArrayOperatorsTest, NOTOperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101

    BitArray result = ~a;
    std::cout << "~a: " << result.to_string() << std::endl;

    EXPECT_EQ(result.to_string(), "01010");
}

TEST(BitArrayOperatorsTest, RightShiftOperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101

    a >>= 3;
    std::cout << "a >> 3: " << a.to_string() << std::endl;

    EXPECT_EQ(a.to_string(), "00010");
}

TEST(BitArrayOperatorsTest, LeftShiftOperator)
{
    BitArray b(5, 0x7800000000000000); // 0b01111

    b <<= 3;
    std::cout << "b << 3: " << b.to_string() << std::endl;

    EXPECT_EQ(b.to_string(), "11000");
}

TEST(BitArrayOperatorsTest, InvalidSizeForLogicalOperators)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray c(6, 0x7800000000000000); // 0b011110

    try
    {
        BitArray result = a & c;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Exception caught for mismatched sizes: " << e.what() << std::endl;
    }
}

TEST(BitArrayMethodsTest, SetAndReset)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010

    a.set(0, false);
    std::cout << "After set(0, false): " << a.to_string() << std::endl;
    EXPECT_EQ(a.to_string(), "001001010");

    a.set();
    std::cout << "After set(): " << a.to_string() << std::endl;
    EXPECT_EQ(a.to_string(), "111111111");

    a.reset(2);
    std::cout << "After reset(2): " << a.to_string() << std::endl;
    EXPECT_EQ(a.to_string(), "110111111");

    a.reset();
    std::cout << "After reset(): " << a.to_string() << std::endl;
    EXPECT_EQ(a.to_string(), "000000000");
}
