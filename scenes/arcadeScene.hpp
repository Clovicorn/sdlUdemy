#ifndef ARCADE_SCENE_H
#define ARCADE_SCENE_H

#include <memory>

#include "scene.hpp"
#include "../graphics/spriteSheet.hpp"

class App;
class Vec2D;

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
    SpriteSheet mSpriteSheet;
};

#endif /* ARCADE_SCENE_H */