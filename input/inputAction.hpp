#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;

struct MousePosition
{
    int32_t xPos;
    int32_t yPos;
};

using InputAction = std::function<void(uint32_t dt, InputState)>;
using MouseMoveAction = std::function<void(const MousePosition &position)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition &mousePosition)>;

struct ButtonAction
{
    InputKey Key;
    InputAction Action;
};

struct MouseButtonAction
{
    MouseButton mouseButton;
    MouseInputAction mouseAction;
};

#endif /* INPUT_ACTION_H */