#pragma once

#include <memory>
#include "scene.hpp"

enum eGame
{
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PAC_MAN,
    NUM_GAMES
};

class ArcadeScene : public Scene
{
public:
    ArcadeScene();
    virtual void Init() override;
    virtual void Draw(Screen &theScreen) override;
    virtual void Update(uint32_t dt) override;
    virtual const std::string &GetSceneName() override;

private:
    std::unique_ptr<Scene> GetScene(eGame game);
    std::string mSceneName = "Arcade Scene";
};