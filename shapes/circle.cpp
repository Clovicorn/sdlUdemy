#include "circle.hpp"
#include <cmath>
#include "../utils/utils.hpp"

Circle::Circle() : Circle(Vec2D::Zero, 0)
{
}

Circle::Circle(const Vec2D &center, float radius) : mRadius(radius)
{
    mPoints.push_back(center);
}

bool Circle::Intersects(const Circle &otherCircle) const
{
    return IsLessThanOrEqual(
        GetCenterPoint().Distance(otherCircle.GetCenterPoint()),
        mRadius + otherCircle.GetRadius());
}
bool Circle::ContainsPoint(Vec2D &point) const
{
    float distance = mPoints[0].Distance(point);
    return mRadius > distance;
}