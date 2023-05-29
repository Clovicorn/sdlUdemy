#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include "../../graphics/animatedSprite.hpp"
#include "../../shapes/aaRectangle.hpp"

class Ship
{
public:
    bool Init();
    void MoveForward();
    void RotateLeft();
    void RotateRight();

private:
    AnimatedSprite mSprite;
    AARectangle mBBox;
};

#endif /* ASTEROIDS_SHIP_H */