#include "vec2d.hpp"
#include <cmath>
#include "utils.hpp"

const Vec2D Vec2D::Zero;

Vec2D::Vec2D() : Vec2D(0, 0)
{
}

Vec2D::Vec2D(float x, float y) : mX(x), mY(y)
{
}

ostream &operator<<(ostream &consoleOut, Vec2D &vec)
{
    cout << "X: " << vec.mX << " Y: " << vec.mY << endl;
    return consoleOut;
}

bool Vec2D::operator==(const Vec2D &vec2) const
{
    return IsEqual(mX, vec2.mX) && IsEqual(mY, vec2.mY);
}

bool Vec2D::operator!=(const Vec2D &vec2) const
{
    return !(*this == vec2);
}

Vec2D Vec2D::operator+(const Vec2D &vec) const
{
    return Vec2D(mX + vec.mX, mY + vec.mY);
}

Vec2D &Vec2D::operator+=(const Vec2D &vec)
{
    *this = *this + vec;
    return *this;
}

Vec2D Vec2D::operator-() const
{
    return Vec2D(-mX, -mY);
}

Vec2D Vec2D::operator-(const Vec2D &vec) const
{
    return Vec2D(mX - vec.mX, mY - vec.mY);
}

Vec2D &Vec2D::operator-=(const Vec2D &vec)
{
    *this = *this - vec;
    return *this;
}

Vec2D Vec2D::operator*(float scale) const
{
    return Vec2D(scale * mX, scale * mY);
}

Vec2D &Vec2D::operator*=(float scale)
{
    *this = *this * scale;
    return *this;
}

Vec2D operator*(float scale, const Vec2D &vec)
{
    return vec * scale;
}

Vec2D Vec2D::operator/(float scale) const
{
    assert(fabsf(scale) > EPSILON);

    return Vec2D(mX / scale, mY / scale);
}

Vec2D &Vec2D::operator/=(float scale)
{
    assert(fabsf(scale) > EPSILON);
    *this = *this / scale;
    return *this;
}

float Vec2D::Mag2() const
{
    return mX * mX + mY * mY;
}

float Vec2D::Mag() const
{
    return sqrt(Mag2());
}

Vec2D Vec2D::GetUnitVec() const
{
    float magnitude = Mag();

    if (magnitude > EPSILON)
    {
        return *this / magnitude;
    }

    return Vec2D::Zero;
}

Vec2D &Vec2D::Normalize()
{
    float magnitude = Mag();

    if (magnitude > EPSILON)
    {
        *this /= magnitude;
    }

    return *this;
}

float Vec2D::Distance(const Vec2D &vec) const
{
    return (vec - *this).Mag();
}

float Vec2D::Dot(const Vec2D &vec) const
{
    return mX * vec.mX + mY * vec.mY;
}

Vec2D Vec2D::ProjectOnto(const Vec2D &vec) const
{
    Vec2D unitVec = vec.GetUnitVec();
    float dotProduct = Dot(vec);

    return unitVec * dotProduct;
}

float Vec2D::AngleBetween(const Vec2D &vec) const
{
    return acosf(GetUnitVec().Dot(vec.GetUnitVec()));
}

Vec2D Vec2D::Reflect(const Vec2D &normal) const
{
    return *this - 2 * ProjectOnto(normal);
}

void Vec2D::Rotate(float angle, const Vec2D &aroundPoint)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);
    thisVec -= aroundPoint;
    float rotX = thisVec.mX * cosine - thisVec.mY * sine;
    float rotY = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot(rotX, rotY);
    *this = rot + aroundPoint;
    // RotX = cos*X - sin*Y
    // RotY = sin*X + cos*Y
}
Vec2D Vec2D::RotateResult(float angle, const Vec2D &aroundPoint) const
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);
    thisVec -= aroundPoint;
    float rotX = thisVec.mX * cosine - thisVec.mY * sine;
    float rotY = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot(rotX, rotY);
    return rot + aroundPoint;
}

Vec2D Vec2D::GetGradient(const Vec2D &endPoint, float speed)
{
    float gradient = (mX - endPoint.GetX()) / (mY - endPoint.GetY());

    if (gradient < 0)
    {
        gradient *= -1;
    }

    float ratioXY = speed / (1 + gradient);
    float x = ratioXY * gradient;
    float y = ratioXY;

    return Vec2D(x, y);
}

Vec2D Vec2D::GetGradient(const Vec2D &startPoint, float angle, float length, float speed)
{

    float x2 = startPoint.GetX() + (length * std::cos(angle));
    float y2 = startPoint.GetY() + (length * std::sin(angle));
    return GetGradient(Vec2D(x2, y2), speed);
}