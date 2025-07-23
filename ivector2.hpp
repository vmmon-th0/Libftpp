#ifndef IVECTOR_HPP
#define IVECTOR_HPP

#include "mathematics.hpp"

template<typename TType>
struct IVector2
{
    virtual float length() const = 0;
    virtual IVector2<float> normalize() const = 0;
    virtual float dot(IVector2 const& vec) const = 0;
    virtual IVector2 cross(IVector2 const& vec) const = 0;

    virtual IVector2& operator+=(IVector2 const& vec) = 0;
    virtual IVector2& operator-=(IVector2 const& vec) = 0;
    virtual IVector2& operator*=(IVector2 const& vec) = 0;
    virtual IVector2& operator/=(IVector2 const& vec) = 0;

    virtual std::unique_ptr<IVector2> operator+(IVector2 const& vec) const = 0;
    virtual std::unique_ptr<IVector2> operator-(IVector2 const& vec) const = 0;
    virtual std::unique_ptr<IVector2> operator*(IVector2 const& vec) const = 0;
    virtual std::unique_ptr<IVector2> operator/(IVector2 const& vec) const = 0;

    virtual bool operator==(IVector2 const& vec) const = 0;
    virtual bool operator!=(IVector2 const& vec) const = 0;

    virtual ~IVector2() {}
};

template<typename TType>
struct Vector2 : public IVector2<TType>
{
    TType x;
    TType y;

    Vector2(): x(0), y(0)
    {
    }

    Vector2(TType x, TType y): x(x), y(y)
    {
    }

    ~Vector2()
    {
    }

    float length() const override
    {
        return std::sqrt(x*x + y*y);
    }

    std::unique_ptr<IVector2<float>> normalize() const override
    {
        float len = this->length();
        if (len == 0.f)
        {
            return std::make_unique<Vector2<float>>(0.f, 0.f);
        }
        float nx = static_cast<float>(x) / len;
        float ny = static_cast<float>(y) / len;
        return std::make_unique<Vector2<float>>(nx, ny);
    }

    float dot(IVector2<TType> const& vec) const override
    {
        const Vector2<TType>* vecPtr = dynamic_cast<const Vector2<TType>*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return static_cast<float>(x * vecPtr->x + y * vecPtr->y);
    }

    std::unique_ptr<IVector2<TType>> cross() const override
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return static_cast<float>(x * vecPtr->y - y * vecPtr->x);
    }

    std::unique_ptr<IVector2<TType>> operator+=(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        this->x += vec.x;
        this->y += vec.y;
        return *this;
    }

    std::unique_ptr<IVector2<TType>> operator-=(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        this->x -= vec.x;
        this->y -= vec.y;
        return *this;
    }

    std::unique_ptr<IVector2<TType>> operator+(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return std::make_unique(Vector2<float>(this->x + vec.x, this->y + vec.y));
    }

    std::unique_ptr<IVector2<TType>> operator-(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return std::make_unique(Vector2<float>(this->x - vec.x, this->y - vec.y));
    }

    std::unique_ptr<IVector2<TType>> operator*(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return std::make_unique(Vector2<float>(this->x - vec.x, this->y - vec.y));
    }

    std::unique_ptr<IVector2<TType>> operator/(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        if (!vecPtr)
        {
            throw std::invalid_argument("Mismatched vector types");
        }
        return std::make_unique(Vector2<float>(this->x / vecPtr.x, this->y / vecPtr.y));
    }
    
    bool operator ==(IVector2 const& vec)
    {
        auto vecPtr = dynamic_cast<Vector2 const*>(&vec);
        return vecPtr && this->x == vec.x && this->y == vec.y;
    }
    
    bool operator !=(IVector2 const& vec)
    {
        return !(*this == vec);
    }
};

#endif