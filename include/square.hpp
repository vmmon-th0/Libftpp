#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "rectangle.hpp"

class Square : public Rectangle
{
    public:
        explicit Square(double size = 0);

        void setWidth(double w) override;
        void setHeight(double h) override;
};

#endif