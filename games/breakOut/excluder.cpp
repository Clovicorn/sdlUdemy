#include "excluder.hpp"
#include <cmath>
#include "../../utils/utils.hpp"

void Excluder::Init(const AARectangle &rect, bool reverseNormals)
{
    maaRect = rect;
    mReverseNormals = reverseNormals;
    SetupEdges();
}

bool Excluder::HasCollided(const AARectangle &rect, BoundaryEdge &edge) const
{
    if (maaRect.Intersects(rect))
    {
        float yMin = maaRect.GetTopLeft().GetY() >= (rect.GetTopLeft().GetY()) ? maaRect.GetTopLeft().GetY() : rect.GetTopLeft().GetY();
        float yMax = maaRect.GetBottomRight().GetY() <= rect.GetBottomRight().GetY() ? maaRect.GetBottomRight().GetY() : rect.GetBottomRight().GetY();
        float ySize = yMax - yMin;

        float xMin = maaRect.GetTopLeft().GetX() >=
                             rect.GetTopLeft().GetX()
                         ? maaRect.GetTopLeft().GetX()
                         : rect.GetTopLeft().GetX();
        float xMax = maaRect.GetBottomRight().GetX() <=
                             rect.GetBottomRight().GetX()
                         ? maaRect.GetBottomRight().GetX()
                         : rect.GetBottomRight().GetX();

        float xSize = xMax - xMin;

        if (xSize > ySize)
        {
            if (rect.GetCenterPoint().GetY() > maaRect.GetCenterPoint().GetY())
            {
                edge = mEdges[BOTTOM_EDGE];
            }
            else
            {
                edge = mEdges[TOP_EDGE];
            }
        }
        else
        {
            if (rect.GetCenterPoint().GetX() < maaRect.GetCenterPoint().GetX())
            {
                edge = mEdges[LEFT_EDGE];
            }
            else
            {
                edge = mEdges[RIGHT_EDGE];
            }
        }
        return true;
    }

    return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle &rect) const
{
    BoundaryEdge edge;
    Vec2D offset = Vec2D::Zero;

    if (HasCollided(rect, edge))
    {
        float yMin = maaRect.GetTopLeft().GetY() >=
                             rect.GetTopLeft().GetY()
                         ? maaRect.GetTopLeft().GetY()
                         : rect.GetTopLeft().GetY();
        float yMax = maaRect.GetBottomRight().GetY() <= rect.GetBottomRight().GetY() ? maaRect.GetBottomRight().GetY() : rect.GetBottomRight().GetY();

        float ySize = yMax - yMin;

        float xMin = maaRect.GetTopLeft().GetX() >= rect.GetTopLeft().GetX() ? maaRect.GetTopLeft().GetX() : rect.GetTopLeft().GetX();
        float xMax = maaRect.GetBottomRight().GetX() <= rect.GetBottomRight().GetX() ? maaRect.GetBottomRight().GetX() : rect.GetBottomRight().GetX();
        float xSize = xMax - xMin;

        if (IsEqual(edge.normal.GetY(), 0))
        {
            offset = (ySize + 1) * edge.normal;
        }
        else
        {
            offset = (xSize + 1) * edge.normal;
        }
    }

    return offset;
}

void Excluder::MoveBY(const Vec2D &delta)
{
    maaRect.MoveBy(delta);
    SetupEdges();
}

void Excluder::MoveTo(const Vec2D &point)
{
    maaRect.MoveTo(point);
    SetupEdges();
}

const BoundaryEdge &Excluder::GetEdge(EdgeType edge) const
{
    if (edge < NUM_EDGES)
    {
        return mEdges[edge];
    }

    return mEdges[NUM_EDGES];
}

void Excluder::SetupEdges()
{
    mEdges[EdgeType::TOP_EDGE].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetTopLeft().GetY()));
    mEdges[EdgeType::TOP_EDGE].normal = UP_DIR;

    mEdges[EdgeType::RIGHT_EDGE].edge = Line2D(Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EdgeType::RIGHT_EDGE].normal = RIGHT_DIR;

    mEdges[EdgeType::BOTTOM_EDGE].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetBottomRight().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EdgeType::BOTTOM_EDGE].normal = DOWN_DIR;

    mEdges[EdgeType::LEFT_EDGE].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EdgeType::LEFT_EDGE].normal = LEFT_DIR;

    mEdges[NUM_EDGES].edge = mEdges[TOP_EDGE].edge;
    mEdges[NUM_EDGES].normal = UP_DIR;

    if (mReverseNormals)
    {
        for (auto &edge : mEdges)
        {
            edge.normal = -edge.normal;
        }
    }
}