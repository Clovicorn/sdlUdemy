#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <memory>
#include "scene.hpp"
class Game;

class GameScene : public Scene
{
public:
    GameScene(std::unique_ptr<Game> ptrGame);
    virtual ~GameScene() {}
    virtual void Init() override;
    virtual void Draw(Screen &screen) override;
    virtual void Update(uint32_t dt) override;
    virtual const std::string &GetSceneName() override;

protected:
    std::unique_ptr<Game> mGame;
    std::string mName;
};

#endif /* GAME_SCENE_H */