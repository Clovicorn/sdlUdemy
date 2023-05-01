#pragma once

#include "boundaryEdge.hpp"
#include "../../shapes/aaRectangle.hpp"
#include <cmath>
#include "../../utils/utils.hpp"

class Excluder
{
public:
    virtual ~Excluder() {}
    void Init(const AARectangle &rect, bool reverseNormals = false);
    bool HasCollided(const AARectangle &rect, BoundaryEdge &edge) const;
    Vec2D GetCollisionOffset(const AARectangle &rect) const;
    inline AARectangle GetAARectangle() const { return maaRect; }
    void MoveBY(const Vec2D &Delta);
    void MoveTo(const Vec2D &point);
    const BoundaryEdge GetEdge(EDGE_TYPE edge);
    inline const Vec2D GetTopLeft() { return maaRect.GetTopLeft(); }
    inline const Vec2D GetBottomRight() { return maaRect.GetBottomRight(); }

private:
    void SetupEdges();
    AARectangle maaRect;
    BoundaryEdge mEdges[NUM_EDGES];
    bool mReverseNormals;
};