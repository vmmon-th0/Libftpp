#ifndef PERLIN_NOISE_2D_HPP
#define PERLIN_NOISE_2D_HPP

#include "ivector2.hpp"
#include "random_2D_coordinate_generator.hpp"

const int WIDTH = 50;
const int HEIGHT = 25;
const int GRID_SIZE = 8;

class PerlinNoise2D
{
    public:
        PerlinNoise2D(int64_t seed);
        ~PerlinNoise2D();

        float sample(int x, int y);
        IVector2<float> randomGradient(int ix, int iy);
        float dotGridGradient(int ix, int iy, float x, float y);
        float fade(float t);
        float lerp(float a, float b, float t);
        float perlin(float x, float y);

    private:
        Random2DCoordinateGenerator _pnrg;
};

#endif