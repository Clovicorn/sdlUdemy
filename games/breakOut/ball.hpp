#ifndef BALL_H
#define BALL_H

#include "../../shapes/aaRectangle.hpp"
#include "../../shapes/circle.hpp"

class Screen;
struct BoundaryEdge;

class Ball
{
public:
    Ball();
    Ball(const Vec2D &pos, float radius);

    void Bounce(const BoundaryEdge &edge);
    void Update(uint32_t dt);
    void Draw(Screen &screen);
    void MakeFlushWithEdge(const BoundaryEdge &edge, Vec2D &pointOnEdge, bool limitToEdge);
    void MoveTo(const Vec2D &point);
    void SetRadius(float radius);

    inline const AARectangle GetBoundingRect() const { return mBBox; }
    inline void Stop() { mVelocity = Vec2D::Zero; }
    inline Vec2D GetVelocity() { return mVelocity; }
    inline float GetRadius() { return mBBox.GetWidth() / 2.0f; }
    inline Vec2D GetPosition() { return mBBox.GetCenterPoint(); }
    inline void SetVelocity(const Vec2D &velocity) { mVelocity = velocity; }
    inline void UpdateScore(int amount) { mScore += amount; }
    inline int GetScore() { return mScore; }
    inline void ResetScore() { mScore = 2000; }

private:
    int mScore = 0;
    AARectangle mBBox;
    Vec2D mVelocity;
    const float RADIUS = 5.0f;
};

#endif /* BALL_H */