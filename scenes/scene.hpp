#pragma once

#include <string>
#include <stdint.h>
#include "../graphics/screen.hpp"
#include "../input/gameController.hpp"

class Scene
{
public:
    virtual ~Scene() {}
    virtual void Init() = 0;
    virtual void Draw(Screen &screen) = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual const std::string &GetSceneName() = 0;
    GameController *GetGameController() { return &mGameController; }

protected:
    GameController mGameController;
};