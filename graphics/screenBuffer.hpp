#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <stdint.h>
#include <assert.h>

#include "color.hpp"

struct SDL_Surface;

class ScreenBuffer
{

public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer &ScreenBuffer);
    ~ScreenBuffer();

    ScreenBuffer &operator=(const ScreenBuffer &screenBuffer);
    void Init(uint32_t format, uint32_t width, uint32_t height);
    void Clear(const Color &color = Color::Black());
    void SetPixel(Color color, int x, int y);
    SDL_Surface *GetSurface();

private:
    SDL_Surface *mSurface;
    uint32_t GetIndex(int row, int column);
};

#endif /* SCREEN_BUFFER_H */