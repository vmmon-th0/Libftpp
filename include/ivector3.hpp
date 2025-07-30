#ifndef IVECTOR3_HPP
#define IVECTOR3_HPP

#include <cmath>
#include <type_traits>

template <typename TType> struct IVector3
{
        TType x;
        TType y;
        TType z;

        constexpr IVector3() noexcept : x(0), y(0), z(0)
        {
        }

        constexpr IVector3(TType x, TType y, TType z) noexcept : x(x), y(y), z(z)
        {
        }

        constexpr float length() const noexcept
        {
            return std::hypot(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
        }

        constexpr IVector3<float> normalize() const noexcept
        {
            float len = length();
            if (len == 0.f)
                return IVector3<float>(0.f, 0.f, 0.f);

            return IVector3<float>(static_cast<float>(x) / len, static_cast<float>(y) / len,
                                   static_cast<float>(z) / len);
        }

        constexpr float dot(IVector3 const &vec) const noexcept
        {
            return static_cast<float>(x) * static_cast<float>(vec.x) +
                   static_cast<float>(y) * static_cast<float>(vec.y) +
                   static_cast<float>(z) * static_cast<float>(vec.z);
        }

        constexpr IVector3<float> cross(IVector3 const &vec) const noexcept
        {
            return IVector3<float>(
                static_cast<float>(y) * static_cast<float>(vec.z) - static_cast<float>(z) * static_cast<float>(vec.y),

                static_cast<float>(z) * static_cast<float>(vec.x) - static_cast<float>(x) * static_cast<float>(vec.z),

                static_cast<float>(x) * static_cast<float>(vec.y) - static_cast<float>(y) * static_cast<float>(vec.x));
        }

        constexpr IVector3 &operator+=(IVector3 const &vec) noexcept
        {
            x += vec.x;
            y += vec.y;
            z += vec.z;
            return *this;
        }

        constexpr IVector3 &operator-=(IVector3 const &vec) noexcept
        {
            x -= vec.x;
            y -= vec.y;
            z -= vec.z;
            return *this;
        }

        constexpr IVector3 &operator*=(IVector3 const &vec) noexcept
        {
            x *= vec.x;
            y *= vec.y;
            z *= vec.z;
            return *this;
        }

        constexpr IVector3 &operator/=(IVector3 const &vec) noexcept
        {
            x /= vec.x;
            y /= vec.y;
            z /= vec.z;
            return *this;
        }

        // Opérateurs élément‑par‑élément
        constexpr IVector3 operator+(IVector3 const &vec) const noexcept
        {
            return IVector3(x + vec.x, y + vec.y, z + vec.z);
        }

        template <typename U>
        constexpr IVector3<std::common_type_t<TType, U>> operator+(IVector3<U> const &o) const noexcept
        {
            using R = std::common_type_t<TType, U>;
            return IVector3<R>(static_cast<R>(x) + static_cast<R>(o.x), static_cast<R>(y) + static_cast<R>(o.y),
                               static_cast<R>(z) + static_cast<R>(o.z));
        }

        constexpr IVector3 operator-(IVector3 const &vec) const noexcept
        {
            return IVector3(x - vec.x, y - vec.y, z - vec.z);
        }

        constexpr IVector3 operator*(IVector3 const &vec) const noexcept
        {
            return IVector3(x * vec.x, y * vec.y, z * vec.z);
        }

        constexpr IVector3 operator/(IVector3 const &vec) const noexcept
        {
            return IVector3(x / vec.x, y / vec.y, z / vec.z);
        }

        constexpr bool operator==(IVector3 const &vec) const noexcept
        {
            return x == vec.x && y == vec.y && z == vec.z;
        }

        constexpr bool operator!=(IVector3 const &vec) const noexcept
        {
            return !(*this == vec);
        }
};

#endif
