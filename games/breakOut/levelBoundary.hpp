#ifndef LEVEL_BOUNDARY_H
#define LEVEL_BOUNDARY_H

#include "excluder.hpp"
class Ball;

class LevelBoundary
{
public:
    LevelBoundary() {}
    LevelBoundary(const AARectangle &rect);
    bool HasCollided(Ball &ball, BoundaryEdge &edge);
    inline const AARectangle GetRectangle() const { return mIncluder.GetAARectangle(); }

private:
    bool HasCollidedWithEdge(Ball &ball, const BoundaryEdge &edge) const;
    Excluder mIncluder;
};

#endif /* LEVEL_BOUNDARY_H */