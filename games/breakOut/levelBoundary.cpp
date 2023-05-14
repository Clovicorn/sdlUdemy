#include "levelBoundary.hpp"
#include "ball.hpp"

LevelBoundary::LevelBoundary(const AARectangle &rect)
{
    mIncluder.Init(rect, true);
}

bool LevelBoundary::HasCollided(Ball &ball, BoundaryEdge &edge)
{
    for (int i = 0; i < NUM_EDGES; ++i)
    {
        BoundaryEdge collisionEdge = mIncluder.GetEdge(static_cast<EdgeType>(i));
        if (HasCollidedWithEdge(ball, collisionEdge))
        {
            edge = collisionEdge;
            return true;
        }
    }

    return false;
}

bool LevelBoundary::HasCollidedWithEdge(Ball &ball, const BoundaryEdge &edge) const
{
    return edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius();
}
