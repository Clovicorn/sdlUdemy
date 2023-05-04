#pragma once

#include "ball.hpp"
#include "excluder.hpp"

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