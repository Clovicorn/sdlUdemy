#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"

class Circle : public Shape
{
public:
    Circle();
    Circle(const Vec2D &center, float radius);
    virtual inline Vec2D GetCenterPoint() const { return mPoints[0]; }
    inline float GetRadius() const { return mRadius; }
    inline void SetRadius(const float newRadius) { mRadius = newRadius; }
    inline void MoveTo(const Vec2D &point) { mPoints[0] = point; }

    bool Intersects(const Circle &otherCircle) const;
    bool ContainsPoint(Vec2D &point) const;

private:
    float mRadius;
};

#endif /* CIRCLE_H */