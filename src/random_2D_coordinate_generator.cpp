#include "random_2D_coordinate_generator.hpp"

Random2DCoordinateGenerator::Random2DCoordinateGenerator(): _seed(std::chrono::steady_clock::now().time_since_epoch().count())
{
}

Random2DCoordinateGenerator::Random2DCoordinateGenerator(uint_fast64_t seed):_seed(seed)
{
}

long long Random2DCoordinateGenerator::seed()
{
    return this->_seed;
}

long long Random2DCoordinateGenerator::operator()(const long long& x, const long long& y)
{
    long long hashedCoordinates = this->_seed ^ (x * 73856093LL) ^ (y * 19349663LL);
    return hashedCoordinates & 0x7FFFFFFFFFFFFFFFLL;
}