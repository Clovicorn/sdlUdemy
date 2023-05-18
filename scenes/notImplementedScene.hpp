#ifndef SCENE_NOTIMPLEMENTEDSCENE_H
#define SCENE_NOTIMPLEMENTEDSCENE_H

#include <string>
#include "scene.hpp"

class Screen;

class NotImplementedScene : public Scene
{
public:
    virtual void Init() override;
    virtual void Draw(Screen &screen) override;
    virtual void Update(uint32_t dt) override;
    virtual std::string &GetSceneName() override;

private:
    int mTimeElapsed = 0;
    bool mIsPaused = false;
    std::string mSceneName = "Not Implemented!";
};

#endif /* SCENE_NOTIMPLEMENTEDSCENE_H */