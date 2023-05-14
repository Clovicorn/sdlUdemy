#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "../utils/vec2d.hpp"

class Shape
{
public:
    virtual Vec2D GetCenterPoint() const = 0;
    virtual ~Shape() {}
    inline virtual std::vector<Vec2D> GetPoints() { return mPoints; }
    void MoveBy(const Vec2D &deltaOffset);

protected:
    std::vector<Vec2D> mPoints;
};

#endif /* SHAPE_H */