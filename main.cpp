#include <iostream>
#include <SDL2/SDL.h>
#include "app/app.hpp"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 2;

int main(int argc, char *argv[])
{
    bool didInit = false;
    didInit = App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION);
    if (didInit)
    {
        App::Singleton().Run();
    }

    return 0;
}
