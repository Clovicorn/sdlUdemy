#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <SDL2/SDL.h>
#include "inputAction.hpp"
#include "gameController.hpp"

class InputController
{
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t dt);
    void SetGameController(GameController *controller);

private:
    InputAction mQuit;
    GameController *mCurrentController;
};

#endif /* INPUT_CONTROLLER_H */