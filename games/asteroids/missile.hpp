#ifndef ASTEROIDS_MISSILE_H
#define ASTEROIDS_MISSILE_H

#include "../../graphics/animatedSprite.hpp"
#include "../../shapes/aaRectangle.hpp"

class Missile
{
public:
    void Init();
    void Draw(Screen &screen);
    void Update(uint32_t dt);

private:
    int mSpeed;
    AARectangle mBBox;
    AnimatedSprite mSprite;
};
#endif /* ASTEROIDS_MISSILE_H */