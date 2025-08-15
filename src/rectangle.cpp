#include "rectangle.hpp"

constexpr Rectangle::Rectangle(double w, double h) : width(w), height(h)
{
}

Rectangle::~Rectangle() = default;

void Rectangle::setWidth(double w)
{
    width = w;
}

void Rectangle::setHeight(double h)
{
    height = h;
}

constexpr double Rectangle::getWidth() const
{
    return width;
}

constexpr double Rectangle::getHeight() const
{
    return height;
}

constexpr double Rectangle::area() const
{
    return width * height;
}