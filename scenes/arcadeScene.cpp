#include "arcadeScene.hpp"
#include "scene.hpp"
#include "../app/app.hpp"
#include "../utils/vec2d.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../shapes/aaRectangle.hpp"

ArcadeScene::ArcadeScene()
{
}

void ArcadeScene::Init()
{
    ButtonAction action;
    action.Key = GameController::Action();
    action.Action = [](uint32_t dt, InputState state)
    {
        if (state)
        {
            std::cout << "Action key is pressed" << std::endl;
        }
        else
        {
            std::cout << "Action key is released" << std::endl;
        }
    };
    mGameController.AddInputActionForKey(action);
    MouseButtonAction mouseAction;
    mouseAction.mouseButton = GameController::LeftMouseButton();
    mouseAction.mouseAction = [](InputState state, MousePosition position)
    {
        if (state)
        {
            std::cout << "Left mouse button pressed." << std::endl;
        }
        else
        {
            std::cout << "Left mouse released" << std::endl;
        }
    };
    mGameController.AddMouseButtonAction(mouseAction);
}

void ArcadeScene::Draw(Screen &theScreen)
{
    Vec2D drawPoint(10, 10);
    BitmapFont &font = App::Singleton().GetFont();
    AARectangle rect(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height());
    Vec2D textPos = font.GetDrawPosition(GetSceneName(), rect, BFXA_CENTER, BFYA_CENTER);
    theScreen.Draw(font, GetSceneName(), textPos, Color::Red());
}

void ArcadeScene::Update(uint32_t dt)
{
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
    }
    break;
    case (BREAK_OUT):
    {
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
    default:
    {
    }
    }
    return nullptr;
}