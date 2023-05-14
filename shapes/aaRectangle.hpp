#ifndef AARECTANGLE_H
#define AARECTANGLE_H

#include "shape.hpp"

class AARectangle : public Shape
{
public:
    AARectangle();
    AARectangle(const Vec2D &topLeft, unsigned int width, unsigned int height);
    AARectangle(const Vec2D &topLeft, const Vec2D &bottomRight);
    ~AARectangle();

    inline void SetTopLeft(const Vec2D &vec) { mPoints[0] = vec; }
    inline void SetBottomRight(const Vec2D &vec) { mPoints[1] = vec; }
    inline Vec2D GetTopLeft() const { return mPoints[0]; }
    inline Vec2D GetBottomRight() const { return mPoints[1]; }

    float GetWidth() const;
    float GetHeight() const;

    void MoveTo(const Vec2D &pos);

    virtual Vec2D GetCenterPoint() const override;

    bool Intersects(const AARectangle &rect) const;
    bool ContainsPoint(const Vec2D &point) const;

    static AARectangle Inset(const AARectangle &rect, Vec2D &insets);

    virtual std::vector<Vec2D> GetPoints() override;

private:
};

#endif /* AARECTANGLE_H */