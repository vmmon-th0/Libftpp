#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

class Rectangle
{
    public:
        explicit Rectangle(double w = 0, double h = 0);
        virtual ~Rectangle();

        virtual void setWidth(double w);
        virtual void setHeight(double h);

        constexpr double getWidth() const;
        constexpr double getHeight() const;

        constexpr double area() const;

    protected:
        double width;
        double height;
};

#endif