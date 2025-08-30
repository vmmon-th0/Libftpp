#include "perlin_noise_2D.hpp"

PerlinNoise2D::PerlinNoise2D(int64_t seed) : _pnrg(seed)
{
}

PerlinNoise2D::~PerlinNoise2D()
{
}

float PerlinNoise2D::sample(int x, int y)
{
    return this->_pnrg(x, y);
}

IVector2<float> PerlinNoise2D::randomGradient(int ix, int iy)
{
    float angle = fmod(this->_pnrg(ix, iy), 2.0f * M_PI);
    return IVector2(std::cos(angle), std::sin(angle));
}

float PerlinNoise2D::dotGridGradient(int ix, int iy, float x, float y)
{
    IVector2<float> gradient = randomGradient(ix, iy);
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    return dx * gradient.x + dy * gradient.y;
}

float PerlinNoise2D::fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoise2D::lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float PerlinNoise2D::perlin(float x, float y)
{
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    float sx = fade(x - x0);
    float sy = fade(y - y0);

    float n0, n1, ix0, ix1;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);

    return (lerp(ix0, ix1, sy) + 1.0f) / 2.0f;
}