#pragma once

#include <iostream>
#include <assert.h>
#include "utils.hpp"

using namespace std;
class Vec2D
{
public:
    static const Vec2D Zero;
    Vec2D();
    Vec2D(float x, float y);
    inline void SetX(float x) { mX = x; }
    inline void SetY(float y) { mY = y; }
    inline float GetX() const { return mX; }
    inline float GetY() const { return mY; }

    bool operator==(const Vec2D &vec2) const;
    bool operator!=(const Vec2D &vec2) const;

    Vec2D operator+(const Vec2D &vec) const;
    Vec2D &operator+=(const Vec2D &vec);

    Vec2D operator-() const;
    Vec2D operator-(const Vec2D &vec) const;
    Vec2D &operator-=(const Vec2D &vec);

    Vec2D operator*(float scale) const;
    Vec2D &operator*=(float scale);
    friend Vec2D operator*(float scale, const Vec2D &vec);

    Vec2D operator/(float scale) const;
    Vec2D &operator/=(float scale);

    friend ostream &operator<<(ostream &consoleOut, Vec2D &vec);

    float Mag2() const;
    float Mag() const;

    Vec2D GetUnitVec() const;
    Vec2D &Normalize();

    float Distance(const Vec2D &vec) const;
    float Dot(const Vec2D &vec) const;

    Vec2D ProjectOnto(const Vec2D &vec) const;
    float AngleBetween(const Vec2D &vec) const;
    Vec2D Reflect(const Vec2D &normal) const;
    void Rotate(float angle, const Vec2D &aroundPoint);
    Vec2D RotateResult(float angle, const Vec2D &aroundPoint) const;

private:
    float mX;
    float mY;
};