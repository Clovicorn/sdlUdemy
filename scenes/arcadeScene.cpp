#include "arcadeScene.hpp"

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