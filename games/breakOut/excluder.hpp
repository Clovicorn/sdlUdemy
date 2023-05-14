#ifndef EXCLUDER_H
#define EXCLUDER_H

#include "boundaryEdge.hpp"
#include "../../shapes/aaRectangle.hpp"

class Excluder
{
public:
    virtual ~Excluder() {}
    void Init(const AARectangle &rect, bool reverseNormals = false);
    bool HasCollided(const AARectangle &rect, BoundaryEdge &edge) const;
    Vec2D GetCollisionOffset(const AARectangle &rect) const;
    inline const AARectangle GetAARectangle() const { return maaRect; }
    void MoveBY(const Vec2D &Delta);
    void MoveTo(const Vec2D &point);
    const BoundaryEdge &GetEdge(EdgeType edge) const;
    inline const Vec2D GetTopLeft() { return maaRect.GetTopLeft(); }
    inline const Vec2D GetBottomRight() { return maaRect.GetBottomRight(); }

private:
    void SetupEdges();
    AARectangle maaRect;
    BoundaryEdge mEdges[NUM_EDGES + 1];
    bool mReverseNormals;
};

#endif /* EXCLUDER_H */