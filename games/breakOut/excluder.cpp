#include "excluder.hpp"

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
        float yMin = maaRect.GetTopLeft().GetY() >= rect.GetTopLeft().GetY() ? maaRect.GetTopLeft().GetY() : rect.GetTopLeft().GetY();
        float yMax = maaRect.GetBottomRight().GetY() <= rect.GetTopLeft().GetY() ? maaRect.GetBottomRight().GetY() : rect.GetBottomRight().GetY();
        float ySize = yMax - yMin;

        float xMin = maaRect.GetTopLeft().GetX() >= rect.GetTopLeft().GetX() ? maaRect.GetTopLeft().GetX() : rect.GetTopLeft().GetX();
        float xMax = maaRect.GetBottomRight().GetX() <= rect.GetTopLeft().GetX() ? maaRect.GetBottomRight().GetX() : rect.GetBottomRight().GetX();
        float xSize = xMax - xMin;

        if (xSize > ySize)
        {
            if (maaRect.GetCenterPoint().GetY() < rect.GetCenterPoint().GetY())
            {
                edge = mEdges[BOTTOM];
            }
            else
            {
                edge = mEdges[TOP];
            }
        }
        else
        {
            if (maaRect.GetCenterPoint().GetX() < rect.GetCenterPoint().GetX())
            {
                edge = mEdges[RIGHT];
            }
            else
            {
                edge = mEdges[LEFT];
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
        float yMin = maaRect.GetTopLeft().GetY() >= rect.GetTopLeft().GetY() ? maaRect.GetTopLeft().GetY() : rect.GetTopLeft().GetY();
        float yMax = maaRect.GetBottomRight().GetY() <= rect.GetTopLeft().GetY() ? maaRect.GetBottomRight().GetY() : rect.GetBottomRight().GetY();
        float ySize = yMax - yMin;

        float xMin = maaRect.GetTopLeft().GetX() >= rect.GetTopLeft().GetX() ? maaRect.GetTopLeft().GetX() : rect.GetTopLeft().GetX();
        float xMax = maaRect.GetBottomRight().GetX() <= rect.GetTopLeft().GetX() ? maaRect.GetBottomRight().GetX() : rect.GetBottomRight().GetX();
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

const BoundaryEdge Excluder::GetEdge(EDGE_TYPE edge)
{
    if (edge != NUM_EDGES)
    {
        return mEdges[edge];
    }
    struct BoundaryEdge newEdge;
    newEdge.normal = Vec2D(0, 0);
    newEdge.edge = Line2D(newEdge.normal, newEdge.normal);
    return newEdge;
}

void Excluder::SetupEdges()
{
    mEdges[EDGE_TYPE::TOP].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetTopLeft().GetY()));
    mEdges[EDGE_TYPE::TOP].normal = UP_DIR;

    mEdges[EDGE_TYPE::RIGHT].edge = Line2D(Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EDGE_TYPE::RIGHT].normal = RIGHT_DIR;

    mEdges[EDGE_TYPE::BOTTOM].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetBottomRight().GetY()), Vec2D(maaRect.GetBottomRight().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EDGE_TYPE::BOTTOM].normal = BOTTOM_DIR;

    mEdges[EDGE_TYPE::LEFT].edge = Line2D(Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetTopLeft().GetY()), Vec2D(maaRect.GetTopLeft().GetX(), maaRect.GetBottomRight().GetY()));
    mEdges[EDGE_TYPE::LEFT].normal = LEFT_DIR;

    if (mReverseNormals)
    {
        for (auto &edge : mEdges)
        {
            edge.normal = -edge.normal;
        }
    }
}