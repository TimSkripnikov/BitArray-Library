#include "BitArray.hpp"
#include <gtest/gtest.h>

TEST(BitArrayConstructorTest, BasicInitialization)
{
    BitArray b(64, 0b1010);
    EXPECT_EQ(b.size(), 64);
    EXPECT_TRUE(b[60]);
    EXPECT_FALSE(b[61]);
    EXPECT_TRUE(b[62]);
    EXPECT_FALSE(b[63]);
}

TEST(BitArrayConstructorTest, NegativeInitialization)
{
    EXPECT_THROW(BitArray b(-5), std::invalid_argument);
}

TEST(BitArrayConstructorTest, ZeroInitialization)
{
    BitArray b(0);
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArraySetTest, BasicSetFunction)
{
    BitArray b(16);
    b.set(0, true);
    b.set(1, true);
    EXPECT_TRUE(b[0]);
    EXPECT_TRUE(b[1]);
}

TEST(BitArraySetTest, OutOfBounds)
{
    BitArray b(16);
    EXPECT_THROW(b.set(16, true), std::range_error);
}

TEST(BitArraySetTest, FullSet)
{
    BitArray b(64);
    b.set();
    for (int i = 0; i < b.size(); ++i)
    {
        EXPECT_TRUE(b[i]);
    }
}

TEST(BitArrayResetTest, BasicResetFunction)
{
    BitArray b(8, 0b11111111);
    b.reset(0);
    b.reset(1);
    EXPECT_FALSE(b[0]);
    EXPECT_FALSE(b[1]);
    EXPECT_TRUE(b[2]);
}

TEST(BitArrayAnyTest, AnyWithTrueBits)
{
    BitArray b(16, 0b1000);
    EXPECT_TRUE(b.any());
}

TEST(BitArrayAnyTest, AnyWithNoBitsSet)
{
    BitArray b(16);
    EXPECT_FALSE(b.any());
}

TEST(BitArrayAnyTest, LargeBitArray)
{
    BitArray b(128);
    EXPECT_FALSE(b.any());
    b.set(100, true);
    EXPECT_TRUE(b.any());
}

TEST(BitArrayCountTest, CountBitsSet)
{
    BitArray b(8, 0b10101010);
    EXPECT_EQ(b.count(), 4);
}

TEST(BitArrayCountTest, CountWithZeroBitsSet)
{
    BitArray b(16);
    EXPECT_EQ(b.count(), 0);
}

TEST(BitArrayCountTest, LargeCount)
{
    BitArray b(128);
    b.set();
    EXPECT_EQ(b.count(), 128);
}

TEST(BitArrayResizeTest, IncreaseSize)
{
    BitArray b(8, 0b10101010);
    b.resize(16, true);
    EXPECT_EQ(b.size(), 16);
    EXPECT_TRUE(b[15]);
}

TEST(BitArrayResizeTest, DecreaseSize)
{
    BitArray b(16, 0b1111111111111111);
    b.resize(8);
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b.count(), 8);
}

TEST(BitArrayResizeTest, ResizingToLargerCapacity)
{
    BitArray b(32, 0b101010);
    b.resize(64, true);
    EXPECT_EQ(b.size(), 64);
    for (int i = 32; i < 64; ++i)
    {
        EXPECT_TRUE(b[i]);
    }
}

TEST(BitArrayResizeTest, ResizeToZero)
{
    BitArray b(16, 0b1010101010101010);
    b.resize(0);
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayOperatorXOR, XOROperation)
{
    BitArray b1(8, 0b10101010);
    BitArray b2(8, 0b11001100);
    BitArray result = b1 ^ b2;
    EXPECT_EQ(result[0], false);
    EXPECT_EQ(result[1], true);
    EXPECT_EQ(result[2], false);
    EXPECT_EQ(result[3], true);
    EXPECT_EQ(result[4], true);
    EXPECT_EQ(result[5], false);
    EXPECT_EQ(result[6], false);
    EXPECT_EQ(result[7], true);
}

TEST(BitArrayOperatorXOR, XORDifferentSizes)
{
    BitArray b1(8, 0b10101010);
    BitArray b2(16, 0b11001100);
    EXPECT_THROW(BitArray result = b1 ^ b2, std::invalid_argument);
}

TEST(BitArrayOperatorShiftLeft, ShiftLeft)
{
    BitArray b(8, 0b1100);
    BitArray result = b << 2;
    EXPECT_FALSE(result[0]);
    EXPECT_FALSE(result[1]);
    EXPECT_TRUE(result[2]);
    EXPECT_TRUE(result[3]);
}

TEST(BitArrayOperatorShiftRight, ShiftRight)
{
    BitArray b(8, 0b1100);
    BitArray result = b >> 2;
    EXPECT_FALSE(result[7]);
    EXPECT_FALSE(result[6]);
    EXPECT_TRUE(result[5]);
    EXPECT_TRUE(result[4]);
}

TEST(BitArrayToStringTest, ToStringWithSpaces)
{
    BitArray b(8, 0b10101010);
    EXPECT_EQ(b.to_string(), "10101010");
}

TEST(BitArrayToStringTest, LargeToString)
{
    BitArray b(16, 0b1111000011110000);
    EXPECT_EQ(b.to_string(), "1111000011110000");
}

TEST(BitArrayEmptyTest, CheckIfEmpty)
{
    BitArray b;
    EXPECT_TRUE(b.empty());
}

TEST(BitArrayPushBackTest, PushBackOneBit)
{
    BitArray b(8, 0b10101010);
    b.push_back(true);
    EXPECT_TRUE(b[8]);
    EXPECT_EQ(b.size(), 9);
}

TEST(BitArrayPushBackTest, PushBackMultipleBits)
{
    BitArray b(4, 0b1010);
    b.push_back(false);
    b.push_back(true);
    EXPECT_EQ(b.size(), 6);
    EXPECT_FALSE(b[4]);
    EXPECT_TRUE(b[5]);
}

TEST(BitArrayPushBackTest, PushBackBeyondMaxSize)
{
    BitArray b(64, 0b11111111);
    EXPECT_THROW(b.push_back(true), std::overflow_error);
}

TEST(BitArrayResizeTest, ResizeToLargeValue)
{
    BitArray b(64, 0b10101010);
    EXPECT_NO_THROW(b.resize(1024));
    EXPECT_EQ(b.size(), 1024);
}

TEST(BitArrayConstructorTest, MaxSizeConstructor)
{
    size_t max_bits = sizeof(unsigned long) * 8;
    BitArray b(max_bits);
    EXPECT_EQ(b.size(), max_bits);
}

TEST(BitArrayConstructorTest, TooLargeConstructor)
{
    size_t max_bits = SIZE_MAX / 2;
    EXPECT_THROW(BitArray b(max_bits), std::bad_alloc);
}
