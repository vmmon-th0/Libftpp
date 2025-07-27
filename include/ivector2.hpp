#ifndef IVECTOR2_HPP
#define IVECTOR2_HPP

#include "mathematics.hpp"

template<typename TType>
struct IVector2
{
    TType x;
    TType y;

    constexpr IVector2() noexcept: x(0), y(0)
    {
    }

    constexpr IVector2(TType x, TType y) noexcept: x(x), y(y)
    {
    }
    
    constexpr float length() const noexcept
    {
        return std::hypot(static_cast<float>(x), static_cast<float>(y));
    }

    constexpr IVector2<float> normalize() const noexcept
    {
        float len = length();
        if (len == 0.f)
        {
            return IVector2<float>(0.f, 0.f);
        }
        float nx = static_cast<float>(x) / len;
        float ny = static_cast<float>(y) / len;
        return IVector2<float>(nx, ny);
    }

    constexpr float dot(const IVector2& vec) const noexcept
    {
        return static_cast<float>(x) * static_cast<float>(vec.x) + static_cast<float>(y) * static_cast<float>(vec.y);
    }

    constexpr IVector2<float> cross(IVector2 const& vec) const noexcept
    {
        return IVector2(-static_cast<float>(y), static_cast<float>(x));
    }

    constexpr IVector2& operator+=(IVector2 const& vec) noexcept
    {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    constexpr IVector2& operator-=(IVector2 const& vec) noexcept
    {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    constexpr IVector2 operator+(IVector2 const& vec) const noexcept
    {
        return IVector2(x + vec.x, y + vec.y);
    }

    template<typename U>
    constexpr IVector2<std::common_type_t<TType,U>> operator+(IVector2<U> const& o) const noexcept
    {
        using R = std::common_type_t<TType,U>;
        return IVector2<R>(static_cast<R>(x) + static_cast<R>(o.x), static_cast<R>(y) + static_cast<R>(o.y));
    }

    constexpr IVector2 operator-(IVector2 const& vec) const noexcept
    {
        return IVector2(x - vec.x, y - vec.y);
    }

    constexpr IVector2 operator*(IVector2 const& vec) const noexcept
    {
        return IVector2(x * vec.x, y * vec.y);
    }

    constexpr IVector2 operator/(IVector2 const& vec) const noexcept
    {
        return IVector2(x / vec.x, y / vec.y);
    }
    
    constexpr bool operator ==(IVector2 const& vec) const noexcept
    {
        return x == vec.x && y == vec.y;
    }
    
    constexpr bool operator !=(IVector2 const& vec) const noexcept
    {
        return !(*this == vec);
    }
};

#endif