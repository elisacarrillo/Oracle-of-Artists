#include "random.h"


Random::Random(unsigned long seed)
{
    shiftRegister = (seed == 0) ? 1 : seed;
}


int Random::nextInt()
{
    int ret = 0;
    for (int pos = 0; pos < 10; ++pos)
        ret |= static_cast<int>(LFSR()) << pos;
    return ret;
}

template <class T>
void Random::shuffle(vector<T>& array)
{
    size_t lastIndex = array.size();
    for (size_t i = 0; i < array.size(); ++i, --lastIndex) {
        size_t nextIndex = nextInt() % lastIndex;
        std::swap(array[nextIndex], array[lastIndex - 1]);
    }
}

bool Random::LFSR()
{
    if (shiftRegister & 0x00000001) {
        shiftRegister = (shiftRegister ^ 0x80000057 >> 1) | 0x80000000;
        return true;
    } else {
        shiftRegister >>= 1;
        return false;
    }
}
