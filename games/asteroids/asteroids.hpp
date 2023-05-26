#ifndef ASTEROIDS_ASTEROIDS_H
#define ASTEROIDS_ASTEROIDS_H

#include <string>
#include <vector>
#include "../game.hpp"

class Screen;

class Asteroids : public Game
{
public:
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

private:
    std::string mGameName = "Asteroids";
};

#endif /* ASTEROIDS_ASTEROIDS_H */