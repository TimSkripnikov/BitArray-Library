#include "BitArray.hpp"
#include <gtest/gtest.h>

// Что нужно было сделать: конструкции try убрать; swap сам с собой; оператор присваивания сам с собой - or, and, xor. ; кратно 64 и возле.

TEST(BitArrayConstructorTest, ValidInitialization)
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

    EXPECT_THROW(a[70], std::range_error);

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

TEST(BitArrayConstructorTest, ZeroInitialization)
{
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayMethodsTest, Swap)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray b(5, 0xA800000000000000); // 0b10101

    a.swap(b);

    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(a.size(), 5);

    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(a.size(), 5);

    EXPECT_TRUE(a[0]);
    EXPECT_EQ(a[1], 0);
    EXPECT_EQ(a[2], 1);

    EXPECT_TRUE(b[0]);
    EXPECT_EQ(b[4], 0);
    EXPECT_EQ(b[2], 1);

    a.swap(a);
    EXPECT_EQ(a.to_string(), "10101");
}

TEST(BitArrayMethodsTest, AssignmentOperator)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray c;
    c = a;

    EXPECT_TRUE(c[0]);
    EXPECT_EQ(c[1], 0);
    EXPECT_EQ(c[2], 1);

    c = c;
    EXPECT_TRUE(c[0]);
    EXPECT_EQ(c[1], 0);
    EXPECT_EQ(c[2], 1);
}

TEST(BitArrayMethodsTest, Resize)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    EXPECT_EQ(a.size(), 9);
    a.resize(15, true);
    EXPECT_EQ(a.size(), 15);

    EXPECT_EQ(a[0], 1); // a = 101001010111111
    EXPECT_EQ(a[4], 0);

    EXPECT_EQ(a[5], 1);
    EXPECT_EQ(a[14], 1);

    EXPECT_THROW(a[15], std::range_error);

    a.resize(64, false);
    EXPECT_EQ(a.to_string(), "1010010101111110000000000000000000000000000000000000000000000000");
}

TEST(BitArrayMethodsTest, Clear)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.empty(), false);

    a.clear();
    EXPECT_EQ(a.empty(), true);

    EXPECT_THROW(a[2], std::range_error);
}

TEST(BitArrayMethodsTest, Push_back)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    a.push_back(true);                 // 0b1010010101
    EXPECT_EQ(a[9], 1);
    a.push_back(false); // 0b10100101010
    EXPECT_EQ(a[10], 0);
}

TEST(BitArrayMethodsTest, Set)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010

    a.set(0, false);
    EXPECT_EQ(a.to_string(), "001001010");
    a.set();
    EXPECT_EQ(a.to_string(), "111111111");
    EXPECT_THROW(a[10], std::range_error);
}

TEST(BitArrayMethodsTest, Reset)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    a.reset(2);
    EXPECT_EQ(a.to_string(), "100001010");
    a.reset();
    EXPECT_EQ(a.to_string(), "000000000");
}

TEST(BitArrayMethodsTest, Any)
{
    BitArray a(9, 0xA500000000000000); // 0b101001010
    BitArray b(5, 0xA800000000000000); // 0b10101
    EXPECT_EQ(a.any(), true);
    EXPECT_EQ(b.any(), true);
}

TEST(BitArrayMethodsTest, None)
{
    BitArray a(9, 0x0);
    EXPECT_EQ(a.none(), true);
}

TEST(BitArrayMethodsTest, Count)
{
    BitArray b(5, 0xA800000000000000); // 0b10101

    EXPECT_EQ(b.count(), 3);
}

TEST(BitArrayMethodsTest, Size)
{
    BitArray b(5, 0xA800000000000000); // 0b10101
    EXPECT_EQ(b.size(), 5);
}

TEST(BitArrayOperatorsTest, AND_Operator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111
    EXPECT_EQ((a & b).to_string(), "00101");
    EXPECT_EQ((a & a).to_string(), "10101");

    BitArray c(6, 0x7800000000000000); // 0b011110
    EXPECT_THROW((a & c), std::invalid_argument);
}

TEST(BitArrayOperatorsTest, OR_Operator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111
    EXPECT_EQ((a | b).to_string(), "11111");
    EXPECT_EQ((a | a).to_string(), "10101");

    BitArray c(6, 0x7800000000000000); // 0b011110
    EXPECT_THROW((a | c), std::invalid_argument);
}

TEST(BitArrayOperatorsTest, XOR_Operator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    BitArray b(5, 0x7800000000000000); // 0b01111
    EXPECT_EQ((a ^ b).to_string(), "11010");
    EXPECT_EQ((a ^ a).to_string(), "00000");

    BitArray c(6, 0x7800000000000000); // 0b011110
    EXPECT_THROW((a ^ c), std::invalid_argument);
}

TEST(BitArrayOperatorsTest, LeftShiftOperator)
{
    BitArray b(5, 0x7800000000000000); // 0b01111
    b <<= 3;
    EXPECT_EQ(b.to_string(), "11000");
}

TEST(BitArrayOperatorsTest, RightShiftOperator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    a >>= 3;
    EXPECT_EQ(a.to_string(), "00010");

    BitArray d(70, 0xA800000000000000); // 0b10101..0
    EXPECT_EQ((d >> 64).to_string(), "0000000000000000000000000000000000000000000000000000000000000000101010");
}

TEST(BitArrayOperatorsTest, NOT_Operator)
{
    BitArray a(5, 0xA800000000000000); // 0b10101
    EXPECT_EQ((~a).to_string(), "01010");
}
