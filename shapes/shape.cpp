#include "shape.hpp"

void Shape::MoveBy(const Vec2D &deltaOffset)
{
    for (Vec2D &point : mPoints)
    {
        point = point + deltaOffset;
    }
}