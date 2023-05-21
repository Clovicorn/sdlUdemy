#include "arcadeScene.hpp"
#include "gameScene.hpp"
#include "notImplementedScene.hpp"
#include "../app/app.hpp"
#include "../utils/vec2d.hpp"
#include "../games/breakOut/breakOut.hpp"
#include "../games/tetris/tetris.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../graphics/screen.hpp"
#include "../shapes/aaRectangle.hpp"

ArcadeScene::ArcadeScene() : ButtonOptionScene({"Asteroids", "BreakOut", "!pacman", "Tetris"}, Color::Magenta())
{
}

void ArcadeScene::Init()
{
    std::vector<Button::ButtonAction> actions;
    actions.push_back([this]
                      { App::Singleton().PushScene(GetScene(ASTEROIDS)); });
    actions.push_back([this]
                      { App::Singleton().PushScene(GetScene(BREAK_OUT)); });
    actions.push_back([this]
                      { App::Singleton().PushScene(GetScene(PAC_MAN)); });
    actions.push_back([this]
                      { App::Singleton().PushScene(GetScene(TETRIS)); });
    SetButtonActions(actions);
    ButtonOptionScene::Init();

    // TEMP
}

void ArcadeScene::Draw(Screen &theScreen)
{
    ButtonOptionScene::Draw(theScreen);
}

void ArcadeScene::Update(uint32_t dt)
{
    ButtonOptionScene::Update(dt);
}

const std::string &ArcadeScene::GetSceneName()
{
    return mSceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
    switch (game)
    {
    case (TETRIS):
    {
        std::unique_ptr<Tetris> tetris = std::make_unique<Tetris>();
        std::unique_ptr<GameScene> tetrisGame = std::make_unique<GameScene>(std::move(tetris));
        return tetrisGame;
    }
    break;
    case (BREAK_OUT):
    {
        std::unique_ptr<BreakOut> breakout = std::make_unique<BreakOut>();
        std::unique_ptr<GameScene> breakoutGame = std::make_unique<GameScene>(std::move(breakout));
        return breakoutGame;
    }
    break;
    case (ASTEROIDS):
    {
    }
    break;
    case (PAC_MAN):
    {
    }
    break;
    }
    std::unique_ptr<NotImplementedScene> notImplmented = std::make_unique<NotImplementedScene>();
    return notImplmented;
}
