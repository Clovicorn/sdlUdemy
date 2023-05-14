#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include "stdint.h"

#include "color.hpp"
#include "screenBuffer.hpp"

class BMPImage;
class Vec2D;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
class SpriteSheet;
struct Sprite;

class Screen
{
public:
    Screen();
    ~Screen();

    SDL_Window *Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreen();
    inline void SetClearColor(const Color &color) { mClearColor = color; }
    inline uint32_t Width() { return mWidth; }
    inline uint32_t Height() { return mHeight; }

    // draw methods below
    void Draw(int x, int y, const Color &color);
    void Draw(const Vec2D &point, const Color &color);
    void Draw(const Line2D &line, const Color &color);
    void Draw(Triangle &triangle, const Color &color, bool fill = false, const Color &fillColor = Color::White());
    void Draw(AARectangle &rect, const Color &color, bool fill = false, const Color &fillColor = Color::White());
    void Draw(Circle &circle, const Color &color, bool fill = false, const Color &fillColor = Color::White());
    void Draw(BMPImage &image, Vec2D &pos);
    void Draw(BMPImage &image, Sprite &sprite, Vec2D &pos);
    void Draw(SpriteSheet &ss, const std::string &spriteName, Vec2D &pos);

private:
    // Not allowing copying of class
    Screen(const Screen &screen);
    Screen &operator=(const Screen &screen);

    void FillPoly(const std::vector<Vec2D> &points, const Color &color);
    void ClearScreen();
    uint32_t mWidth;
    uint32_t mHeight;

    Color mClearColor;

    ScreenBuffer mBackBuffer;

    SDL_Window *mWindow;
    SDL_Surface *mSurface;
};

#endif /* SCREEN_H_ */