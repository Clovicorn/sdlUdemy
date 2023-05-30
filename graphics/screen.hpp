#ifndef SCREEN_H_
#define SCREEN_H_

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

#include "color.hpp"
#include "screenBuffer.hpp"
#include "../utils/vec2d.hpp"

class BMPImage;
class BitmapFont;
class Line2D;
class Triangle;
class AARectangle;
class Circle;
class SpriteSheet;

struct Sprite;
struct SDL_Renderer;
struct SDL_PixelFormat;
struct SDL_Texture;

struct DrawTransform
{
    Vec2D point = Vec2D::Zero;
    float angle = 0.0f;
    float magnification = 1.0f;
};

class Screen
{
public:
    Screen();
    ~Screen();

    SDL_Window *Init(uint32_t w, uint32_t h, uint32_t mag, bool fast = true);
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
    void Draw(const BMPImage &image, const Sprite &sprite, const Vec2D &pos, const Color &overlayColor = Color::White(), const DrawTransform &transform = DrawTransform());
    void Draw(const SpriteSheet &ss, const std::string &spriteName, const Vec2D &pos, const Color &overlayColor = Color::White(), const DrawTransform &transform = DrawTransform());
    void Draw(const BitmapFont &font, const std::string &text, const Vec2D &pos, const Color &overlayColor = Color::White(), const DrawTransform &transform = DrawTransform());
    void SetRenderColor(const Color &color);

private:
    // Not allowing copying of class
    Screen(const Screen &screen);
    Screen &operator=(const Screen &screen);

    using FillPolyFunc = std::function<Color(uint32_t x, uint32_t y)>;
    void FillPoly(const std::vector<Vec2D> &points, FillPolyFunc func);
    void ClearScreen();

    float CreateOverlayValue(uint8_t val) { return (static_cast<float>(val) / 255.0f); }
    uint32_t mWidth;
    uint32_t mHeight;

    bool mFast;
    Color mClearColor;

    ScreenBuffer mBackBuffer;

    SDL_Window *mWindow;
    SDL_Surface *mSurface;
    SDL_Renderer *mRenderer;
    SDL_Texture *mTexture;
    SDL_PixelFormat *mPixelFormat;
};

#endif /* SCREEN_H_ */