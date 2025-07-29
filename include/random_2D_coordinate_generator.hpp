#ifndef RANDOM_2D_COORDINATE_GENERATOR_HPP
#define RANDOM_2D_COORDINATE_GENERATOR_HPP

#include "mathematics.hpp"

// The Random2DCoordinateGenerator class implement a pseudorandom number generator (PRNG), also known as a deterministic random bit generator (DRBG).
// Its model consists of generating pseudo-random numbers based on 2D coordinates.

// We overload the () operator to generate our PRNG in that way: By multiplying each coordinate by a distinct and "large" prime number,
// we change the numerical "frequency" of each coordinate in integer space. This prevents the same patterns
// (especially linear) in the coordinates from resulting in identical (collision) or similar values after the combination.

// For absolute requirements -> total exclusion of collisions, a bijective approach is required.

// This number can be used to decide whether or not an object is present in a grid, to generate a color or texture etc.

class Random2DCoordinateGenerator
{
    public:
        Random2DCoordinateGenerator();
        Random2DCoordinateGenerator(uint_fast64_t seed);

        long long seed();
        long long operator()(const long long& x, const long long& y);

    private:
        uint_fast64_t _seed;
};

#endif