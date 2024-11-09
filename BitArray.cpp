#include "BitArray.hpp"

int BitArray::count_of_blocks(int n) const
{
    return (int)(ceil((double)n / ozero));
}

BitArray::BitArray() : data(NULL), bit_count(0) {}

BitArray::BitArray(int num_bits, unsigned long value)
{
    if (num_bits <= 0)
    {
        throw std::invalid_argument("Number of bits must be positive!\n");
    }

    value <<= ozero - num_bits;
    this->bit_count = num_bits;

    int length_of_array = count_of_blocks(num_bits);
    this->current_count_of_blocks = length_of_array;

    data = new unlong[length_of_array];

    data[0] = value;

    for (int i = 1; i < length_of_array; ++i)
    {
        data[i] = 0x0;
    }
}

BitArray::~BitArray()
{
    delete[] data;
    data = NULL;
    current_count_of_blocks = 0;
    bit_count = 0;
}

BitArray::BitArray(const BitArray &b)
{
    this->bit_count = b.bit_count;
    this->current_count_of_blocks = b.current_count_of_blocks;
    data = new unlong[current_count_of_blocks];

    for (int i = 0; i < current_count_of_blocks; ++i)
    {
        data[i] = b.data[i];
    }
}

void BitArray::swap(BitArray &b)
{
    unlong *temp_data = this->data;
    this->data = b.data;
    b.data = temp_data;

    int temp_bit_count = this->bit_count;
    this->bit_count = b.bit_count;
    b.bit_count = temp_bit_count;
}

BitArray &BitArray::operator=(const BitArray &b)
{
    if (this == &b)
    {
        return *this;
    }

    delete[] data;

    this->bit_count = b.bit_count;
    this->current_count_of_blocks = b.current_count_of_blocks;

    data = new unlong[current_count_of_blocks];

    for (int i = 0; i < current_count_of_blocks; ++i)
    {
        data[i] = b.data[i];
    }

    return *this;
}

void BitArray::resize(int num_bits, bool value)
{
    if (num_bits <= 0 || num_bits <= this->bit_count)
    {
        throw std::invalid_argument("Number of bits must be positive and greater than current bit count!\n");
    }

    int new_block_count = count_of_blocks(num_bits);

    if (new_block_count != current_count_of_blocks)
    {

        unlong *new_data = new unlong[new_block_count];

        for (int i = 0; i < current_count_of_blocks; ++i)
        {
            new_data[i] = data[i];
        }

        for (int i = current_count_of_blocks; i < new_block_count; ++i)
        {
            if (value)
            {
                new_data[i] = ~0UL;
            }
            else
            {
                new_data[i] = 0UL;
            }
        }

        delete[] data;
        this->data = new_data;
        this->current_count_of_blocks = new_block_count;
    }

    this->bit_count = num_bits;
}

BitArray &BitArray::set(int index, bool value)
{
    if (index >= this->bit_count)
    {
        throw std::range_error("Index is more than length of the array!\n");
    }
    else
    {
        int i = index / this->ozero;
        int j = index % this->ozero;
        int shift = this->ozero - 1;

        unlong mask = 1UL << (shift - j);

        if (value)
        {
            this->data[i] |= mask;
        }
        else
        {
            this->data[i] &= ~mask;
        }
    }

    return *this;
}

void BitArray::clear()
{
    delete[] data;
    data = NULL;
    bit_count = 0;
    current_count_of_blocks = 0;
}

void BitArray::push_back(bool bit)
{
    resize(this->bit_count + 1, bit);
}

BitArray &BitArray::operator&=(const BitArray &b)
{
    if (this->bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array lengths must be equal to!\n");
    }
    else
    {
        for (int i = 0; i < this->current_count_of_blocks; ++i)
        {
            this->data[i] &= b.data[i];
        }
        return *this;
    }
}

BitArray &BitArray::operator|=(const BitArray &b)
{
    if (this->bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array lengths must be equal to!\n");
    }
    else
    {
        for (int i = 0; i < this->current_count_of_blocks; ++i)
        {
            this->data[i] |= b.data[i];
        }
        return *this;
    }
}

BitArray &BitArray::operator^=(const BitArray &b)
{
    if (this->bit_count != b.bit_count)
    {
        throw std::invalid_argument("Array lengths must be equal to!\n");
    }
    else
    {
        for (int i = 0; i < this->current_count_of_blocks; ++i)
        {
            this->data[i] ^= b.data[i];
        }
        return *this;
    }
}

bool BitArray::operator[](int i) const
{
    if (this->bit_count <= i)
    {
        throw std::range_error("Index is too big!\n");
    }
    else
    {
        unlong mask = (1UL << ((ozero - 1) - i));
        unlong tmp = this->data[i / ozero] & mask;
        if (tmp)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

BitArray &BitArray::operator<<=(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Number of bits to shift must be positive!\n");
    }

    if (n > this->bit_count)
    {
        n = this->bit_count;
    }

    for (int i = 0; i < this->bit_count - n; ++i)
    {
        this->set(i, (*this)[i + n]);
    }

    for (int i = this->bit_count - 1; i > this->bit_count - 1 - n; --i)
    {
        this->set(i, false);
    }

    return *this;
}

BitArray &BitArray::operator>>=(int n)
{
    if (n <= 0)
    {
        throw std::invalid_argument("Number of bits to shift must be positive!\n");
    }

    if (n > this->bit_count)
    {
        n = this->bit_count;
    }

    for (int i = this->bit_count - 1; i >= n; --i)
    {
        this->set(i, (*this)[i - n]);
    }

    for (int i = 0; i < n; ++i)
    {
        this->set(i, false);
    }

    return *this;
}

BitArray BitArray::operator<<(int n) const
{

    BitArray shifted = *this;

    shifted <<= n;

    return shifted;
}

BitArray BitArray::operator>>(int n) const
{

    BitArray shifted = *this;

    shifted >>= n;

    return shifted;
}

BitArray &BitArray::set()
{
    unlong mask = ALL_ONE;
    for (int i = 0; i < this->current_count_of_blocks; ++i)
    {
        data[i] |= mask;
    }
    return *this;
}

BitArray &BitArray::reset(int n)
{
    if (n >= this->bit_count)
    {
        throw std::range_error("Index is more than length of the array!\n");
    }

    int i = n / this->ozero;
    int j = n % this->ozero;
    int shift = this->ozero - 1;

    unlong mask = 1UL << (shift - j);

    this->data[i] &= ~mask;

    return *this;
}

BitArray &BitArray::reset()
{
    // unlong mask = ~ALL_ONE;
    for (int i = 0; i < this->current_count_of_blocks; ++i)
    {
        data[i] = 0;
    }
    return *this;
}

bool BitArray::any() const
{
    bool any_bit = false;

    for (int i = 0; (i < this->current_count_of_blocks) && !any_bit; ++i)
    {
        if (this->data[i])
        {
            any_bit = true;
        }
    }

    return any_bit;
}

bool BitArray::none() const
{
    return !(this->any());
}

BitArray BitArray::operator~() const
{
    BitArray inv_array(*this);

    for (int i = 0; i < this->current_count_of_blocks; ++i)
    {
        inv_array.data[i] = ~this->data[i];
    }

    return inv_array;
}

int BitArray::count() const
{
    int cnt = 0;

    for (int i = 0; i < this->bit_count; ++i)
    {
        cnt += (*this)[i];
    }

    return cnt;
}

int BitArray::size() const
{
    return this->bit_count;
}

bool BitArray::empty() const
{
    return bit_count == 0;
}

std::string BitArray::to_string() const
{
    std::string result;
    int shift = ozero - 1;

    for (int i = 0; i < bit_count; ++i)
    {

        int block_index = i / ozero;
        int bit_index = i % ozero;

        bool bit = (data[block_index] >> (shift - bit_index)) & 1UL;
        if (bit)
        {
            result += '1';
        }
        else
        {
            result += '0';
        }
    }

    return result;
}

bool operator==(const BitArray &a, const BitArray &b)
{
    bool flag = true;

    if (a.size() != b.size())
    {
        flag = false;
    }
    else
    {
        for (int i = 0; i < a.size() && flag; ++i)
        {
            if (a[i] != b[i])
            {
                flag = false;
            }
        }
    }

    return flag;
}

bool operator!=(const BitArray &a, const BitArray &b)
{
}
