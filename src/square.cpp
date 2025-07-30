#include "square.hpp"

Square::Square(double size = 0) : Rectangle(size, size)
{
}

void Square::setWidth(double w)
{
    width = height = w;
}

void Square::setHeight(double h)
{
    width = height = h;
}

