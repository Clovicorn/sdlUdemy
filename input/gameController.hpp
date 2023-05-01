#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "inputAction.hpp"

class GameController
{
public:
    GameController();
    InputAction GetActionForKey(InputKey key);
    void AddInputActionForKey(const ButtonAction &buttonAction);
    void ClearAll();

    static bool IsPressed(InputKey key);

    static InputKey Action();
    static InputKey Cancel();
    static InputKey Up();
    static InputKey Down();
    static InputKey Left();
    static InputKey Right();

    inline const MouseMoveAction &GetMouseMovedAction() { return mMouseMovedAction; }
    inline void SetMouseMovedAction(const MouseMoveAction &action) { mMouseMovedAction = action; }

    MouseInputAction GetMouseButtonAction(const MouseButton button);
    void AddMouseButtonAction(const MouseButtonAction &action);

    static MouseButton LeftMouseButton();
    static MouseButton RightMouseButton();

private:
    std::vector<ButtonAction> mButtonActions;
    std::vector<MouseButtonAction> mMouseButtonActions;
    MouseMoveAction mMouseMovedAction;
};