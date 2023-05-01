#include "inputController.hpp"

InputController::InputController() : mQuit(nullptr), mCurrentController(nullptr)
{
}

void InputController::Init(InputAction quitAction)
{
    mQuit = quitAction;
}

void InputController::Update(uint32_t dt)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            mQuit(dt, SDL_PRESSED);
            break;
        }
        case SDL_KEYUP:
        case SDL_KEYDOWN:
        {
            if (mCurrentController)
            {
                InputAction action = mCurrentController->GetActionForKey(event.key.keysym.sym);
                action(dt, static_cast<InputState>(event.key.state));
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (mCurrentController->GetMouseMovedAction())
            {
                MousePosition position;
                position.xPos = event.motion.x;
                position.yPos = event.motion.y;
                mCurrentController->GetMouseMovedAction()(position);
            }
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            MouseInputAction action = mCurrentController->GetMouseButtonAction(static_cast<MouseButton>(event.button.button));
            MousePosition position;
            position.xPos = event.motion.x;
            position.yPos = event.motion.y;
            action(static_cast<InputState>(event.button.state), position);
            break;
        }
        }
    }
}

void InputController::SetGameController(GameController *controller)
{
    mCurrentController = controller;
}