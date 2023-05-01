#include "gameController.hpp"

GameController::GameController() : mMouseMovedAction(nullptr)
{
}

InputAction GameController::GetActionForKey(InputKey key)
{
    for (auto &buttonAction : mButtonActions)
    {
        if (key == buttonAction.Key)
        {
            return buttonAction.Action;
        }
    }
    return [](uint32_t, InputState) {};
}

void GameController::AddInputActionForKey(const ButtonAction &buttonAction)
{
    mButtonActions.push_back(buttonAction);
}

void GameController::ClearAll()
{
    mButtonActions.clear();
}

bool GameController::IsPressed(InputState state)
{
    return state == SDL_PRESSED;
}

InputKey GameController::Action()
{
    return static_cast<InputKey>(SDLK_SPACE);
}

InputKey GameController::Cancel()
{
    return static_cast<InputKey>(SDLK_ESCAPE);
}

InputKey GameController::Up()
{
    return static_cast<InputKey>(SDLK_UP);
}

InputKey GameController::Down()
{
    return static_cast<InputKey>(SDLK_DOWN);
}

InputKey GameController::Left()
{
    return static_cast<InputKey>(SDLK_LEFT);
}

InputKey GameController::Right()
{
    return static_cast<InputKey>(SDLK_RIGHT);
}

MouseInputAction GameController::GetMouseButtonAction(const MouseButton button)
{
    for (auto &buttonAction : mMouseButtonActions)
    {
        if (button == buttonAction.mouseButton)
        {
            return buttonAction.mouseAction;
        }
    }
    return [](InputState state, const MousePosition &pos) {};
}

void GameController::AddMouseButtonAction(const MouseButtonAction &action)
{
    mMouseButtonActions.push_back(action);
}

MouseButton GameController::LeftMouseButton()
{
    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}
MouseButton GameController::RightMouseButton()
{
    return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}