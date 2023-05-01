#include "aaRectangle.hpp"

AARectangle::AARectangle() : AARectangle(Vec2D::Zero, Vec2D::Zero)
{
}

AARectangle::AARectangle(const Vec2D &topLeft, unsigned int width, unsigned int height) : AARectangle(topLeft, Vec2D(topLeft.GetX() + width - 1, topLeft.GetY() + height - 1))
{
}

AARectangle::AARectangle(const Vec2D &topLeft, const Vec2D &bottomRight)
{
    mPoints.push_back(topLeft);
    mPoints.push_back(bottomRight);
}

AARectangle::~AARectangle()
{
}

float AARectangle::GetWidth() const
{
    return mPoints[1].GetX() - mPoints[0].GetX() + 1;
}

float AARectangle::GetHeight() const
{
    return mPoints[1].GetY() - mPoints[0].GetY() + 1;
}

void AARectangle::MoveTo(const Vec2D &pos)
{
    float width = GetWidth();
    float height = GetHeight();
    SetTopLeft(pos);
    SetBottomRight(Vec2D(pos.GetX() + width - 1, pos.GetY() + height - 1));
}

Vec2D AARectangle::GetCenterPoint() const
{
    return Vec2D(mPoints[0].GetX() + GetWidth() / 2.0f, mPoints[0].GetY() + GetHeight() / 2.0f);
}

bool AARectangle::Intersects(const AARectangle &rect) const
{
    bool top = rect.GetBottomRight().GetY() < GetTopLeft().GetY();
    bool right = rect.GetTopLeft().GetX() > GetBottomRight().GetX();
    bool bottom = rect.GetTopLeft().GetY() > GetBottomRight().GetY();
    bool left = rect.GetBottomRight().GetX() < GetTopLeft().GetX();

    return !(top || right || bottom || left);
}
bool AARectangle::ContainsPoint(const Vec2D &point) const
{
    return point.GetX() >= mPoints[0].GetX() && point.GetX() <= mPoints[1].GetX() &&
           point.GetY() >= mPoints[0].GetY() && point.GetY() <= mPoints[1].GetY();
}

AARectangle AARectangle::Inset(const AARectangle &rect, Vec2D &insets)
{
    return AARectangle(rect.GetTopLeft() + insets, rect.GetWidth() - 2 * insets.GetX(), rect.GetHeight() - 2 * insets.GetY());
}

std::vector<Vec2D> AARectangle::GetPoints()
{
    std::vector<Vec2D> vecs;

    vecs.push_back(mPoints[0]);
    vecs.push_back(Vec2D(mPoints[1].GetX(), mPoints[0].GetY()));
    vecs.push_back(mPoints[1]);
    vecs.push_back(Vec2D(mPoints[0].GetX(), mPoints[1].GetY()));

    return vecs;
}