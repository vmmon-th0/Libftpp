#include "rectangle.hpp"

Rectangle::Rectangle(double w = 0, double h = 0) : width(w), height(h)
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

double Rectangle::getWidth() const
{
    return width;
}

double Rectangle::getHeight() const
{
    return height;
}

double Rectangle::area() const
{
    return width * height;
}