#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <utility>

typedef unsigned long unlong;
#define ALL_ONE 0xFFFFFFFFFFFFFFFF

/**
 * Class BitArray
 * Represents a dynamic array of bits with various bitwise operations.
 */
class BitArray
{
private:
    unsigned long *data;                         ///< Pointer to the array of blocks storing the bits.
    const int ozero = sizeof(unsigned long) * 8; ///< Number of bits in one block.
    int bit_count;                               ///< Total number of bits in the BitArray.
    int count_of_blocks(int n) const;            ///< Helper function to calculate required blocks for `n` bits.
    int current_count_of_blocks;                 ///< Current number of blocks allocated.

public:
    /**
     * Default constructor. Initializes an empty BitArray.
     */
    BitArray();

    /**
     * Destructor. Releases allocated memory.
     */
    ~BitArray();

    /**
     * Constructs a BitArray with a specified number of bits and an initial value.
     *
     * @param num_bits The number of bits in the BitArray.
     * @param value The initial value of the bits (stored in the first block, default 0).
     * @throws std::invalid_argument If num_bits is non-positive.
     */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /**
     * Copy constructor. Creates a deep copy of another BitArray.
     *
     * @param b The BitArray to copy.
     */
    BitArray(const BitArray &b);

    /**
     * Swaps the contents of this BitArray with another.
     *
     * @param b The BitArray to swap with.
     */
    void swap(BitArray &b);

    /**
     * Copy assignment operator. Assigns the values of another BitArray to this one.
     *
     * @param b The BitArray to assign from.
     * @return A reference to this BitArray.
     */
    BitArray &operator=(const BitArray &b);

    /**
     * Resizes the BitArray to a new size, filling new bits with the given value.
     *
     * @param num_bits The new size in bits.
     * @param value The value for new bits (true for 1, false for 0).
     * @throws std::invalid_argument If num_bits is non-positive or less than the current size.
     */
    void resize(int num_bits, bool value = false);

    /**
     * Clears the contents of the BitArray, resetting all bits to 0.
     */
    void clear();

    /**
     * Appends a bit to the end of the BitArray, resizing it if necessary.
     *
     * @param bit The bit to append (true for 1, false for 0).
     */
    void push_back(bool bit);

    /**
     * Performs bitwise AND operation with another BitArray.
     *
     * @param b The BitArray to AND with.
     * @return A reference to this BitArray.
     * @throws std::invalid_argument If the sizes of the arrays are not equal.
     */
    BitArray &operator&=(const BitArray &b);

    /**
     * Performs bitwise OR operation with another BitArray.
     *
     * @param b The BitArray to OR with.
     * @return A reference to this BitArray.
     * @throws std::invalid_argument If the sizes of the arrays are not equal.
     */
    BitArray &operator|=(const BitArray &b);

    /**
     * Performs bitwise XOR operation with another BitArray.
     *
     * @param b The BitArray to XOR with.
     * @return A reference to this BitArray.
     * @throws std::invalid_argument If the sizes of the arrays are not equal.
     */
    BitArray &operator^=(const BitArray &b);

    /**
     * Shifts all bits left by `n` positions.
     *
     * @param n The number of positions to shift.
     * @return A reference to this BitArray.
     * @throws std::invalid_argument If `n` is non-positive.
     */
    BitArray &operator<<=(int n);

    /**
     * Shifts all bits right by `n` positions.
     *
     * @param n The number of positions to shift.
     * @return A reference to this BitArray.
     * @throws std::invalid_argument If `n` is non-positive.
     */
    BitArray &operator>>=(int n);

    /**
     * Creates a new BitArray shifted left by `n` positions.
     *
     * @param n The number of positions to shift.
     * @return A new BitArray containing the shifted result.
     */
    BitArray operator<<(int n) const;

    /**
     * Creates a new BitArray shifted right by `n` positions.
     *
     * @param n The number of positions to shift.
     * @return A new BitArray containing the shifted result.
     */
    BitArray operator>>(int n) const;

    /**
     * Sets a specific bit in the BitArray to the given value.
     *
     * @param n The index of the bit to set.
     * @param val The value to set (true for 1, false for 0, default true).
     * @return A reference to this BitArray.
     * @throws std::range_error If the index is out of bounds.
     */
    BitArray &set(int n, bool val = true);

    /**
     * Sets all bits in the BitArray to 1.
     *
     * @return A reference to this BitArray.
     */
    BitArray &set();

    /**
     * Resets a specific bit in the BitArray to 0.
     *
     * @param n The index of the bit to reset.
     * @return A reference to this BitArray.
     * @throws std::range_error If the index is out of bounds.
     */
    BitArray &reset(int n);

    /**
     * Resets all bits in the BitArray to 0.
     *
     * @return A reference to this BitArray.
     */
    BitArray &reset();

    /**
     * Checks if any bit in the BitArray is set to 1.
     *
     * @return True if at least one bit is 1, false otherwise.
     */
    bool any() const;

    /**
     * Checks if all bits in the BitArray are set to 0.
     *
     * @return True if no bits are set, false otherwise.
     */
    bool none() const;

    /**
     * Creates a new BitArray with all bits inverted.
     *
     * @return A new BitArray containing the inverted result.
     */
    BitArray operator~() const;

    /**
     * Counts the number of bits set to 1 in the BitArray.
     *
     * @return The count of bits set to 1.
     */
    int count() const;

    /**
     * Accesses the value of a specific bit in the BitArray.
     *
     * @param i The index of the bit to access.
     * @return True if the bit is 1, false otherwise.
     * @throws std::range_error If the index is out of bounds.
     */
    bool operator[](int i) const;

    /**
     * Returns the total number of bits in the BitArray.
     *
     * @return The size of the BitArray.
     */
    int size() const;

    /**
     * Checks if the BitArray is empty (contains no bits).
     *
     * @return True if the BitArray is empty, false otherwise.
     */
    bool empty() const;

    /**
     * Converts the BitArray to a string representation of bits.
     *
     * @return A string representing the bits in the BitArray.
     */
    std::string to_string() const;
};

/**
 * Checks if two BitArrays are equal.
 *
 * @param a The first BitArray.
 * @param b The second BitArray.
 * @return True if the BitArrays are equal, false otherwise.
 */
bool operator==(const BitArray &a, const BitArray &b);

/**
 * Checks if two BitArrays are not equal.
 *
 * @param a The first BitArray.
 * @param b The second BitArray.
 * @return True if the BitArrays are not equal, false otherwise.
 */
bool operator!=(const BitArray &a, const BitArray &b);

/**
 * Performs bitwise AND operation on two BitArrays.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray containing the result.
 * @throws std::invalid_argument If the sizes of the arrays are not equal.
 */
BitArray operator&(const BitArray &b1, const BitArray &b2);

/**
 * Performs bitwise OR operation on two BitArrays.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray containing the result.
 * @throws std::invalid_argument If the sizes of the arrays are not equal.
 */
BitArray operator|(const BitArray &b1, const BitArray &b2);

/**
 * Performs bitwise XOR operation on two BitArrays.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray containing the result.
 * @throws std::invalid_argument If the sizes of the arrays are not equal.
 */
BitArray operator^(const BitArray &b1, const BitArray &b2);
