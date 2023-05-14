#include "paddle.hpp"
#include "boundaryEdge.hpp"
#include "ball.hpp"
#include "../../graphics/screen.hpp"
#include "../../utils/utils.hpp"

void Paddle::Init(AARectangle &rect, int screenWidth, int screenHeight)
{
    mScreenWidth = screenWidth;
    mScreenHeight = screenHeight;
    Excluder::Init(rect);
}

void Paddle::Update(uint32_t dt, Ball &ball)
{
    // if (GetAARectangle().ContainsPoint(ball.GetPosition()))
    // {
    //     Vec2D pointOnEdge;
    //     ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
    // }

    if (mDirection != 0)
    {
        float dtToSeconds = MillisecondsToSeconds(dt);
        Vec2D dir = mDirection == PaddleDirection::LEFT_MOVE ? LEFT_DIR : RIGHT_DIR;
        if (mDirection == PaddleDirection::LEFT_MOVE + PaddleDirection::RIGHT_MOVE)
        {
            dir = Vec2D::Zero;
        }
        Vec2D dX = dir * VELOCITY * dtToSeconds;

        MoveBY(dX);
    }
    switch (mDirection)
    {
    case PaddleDirection::LEFT_MOVE:
    {
        if (GetTopLeft().GetX() < 0)
        {
            MoveTo(Vec2D(0, GetTopLeft().GetY()));
        }
    }
    break;
    case PaddleDirection::RIGHT_MOVE:
    {
        if (GetBottomRight().GetX() > mScreenWidth)
        {
            MoveTo(Vec2D(mScreenWidth - Paddle::PADDLE_WIDTH, GetTopLeft().GetY()));
        }
    }
    break;
    }
}

void Paddle::Draw(Screen &screen)
{
    AARectangle rect = GetAARectangle();
    screen.Draw(rect, Color::Blue(), true, Color::Blue());
}

bool Paddle::Bounce(Ball &ball)
{

    BoundaryEdge edge;
    if (HasCollided(ball.GetBoundingRect(), edge))
    {
        Vec2D pointOnEdge;
        ball.MakeFlushWithEdge(edge, pointOnEdge, true);
        if (edge.edge == GetEdge(TOP_EDGE).edge)
        {
            float edgeLength = edge.edge.Length();
            if (!IsEqual(edgeLength, 0))
            {

                float tx = (pointOnEdge.GetX() - edge.edge.GetP0().GetX()) / edgeLength;
                if ((tx <= CORNER_EDGE_AMOUNT && ball.GetVelocity().GetX() > 0) || (tx >= (1.0f - CORNER_EDGE_AMOUNT) && ball.GetVelocity().GetX() < 0))
                {
                    ball.SetVelocity(-ball.GetVelocity());
                    return true;
                }
            }
        }
        ball.SetVelocity(ball.GetVelocity().Reflect(edge.normal));
        return true;
    }
    return false;
}