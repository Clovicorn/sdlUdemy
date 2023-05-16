#include "screen.hpp"

#include "bmpImage.hpp"
#include "bitmapFont.hpp"
#include "../utils/vec2d.hpp"
#include "../utils/utils.hpp"
#include "../shapes/line2D.hpp"
#include "../shapes/triangle.hpp"
#include "../shapes/aaRectangle.hpp"
#include "../shapes/circle.hpp"
#include "spriteSheet.hpp"

Screen::Screen() : mWindow(nullptr), mSurface(nullptr), mRenderer(nullptr), mTexture(nullptr), mPixelFormat(nullptr), mWidth(0), mHeight(0)
{
}
Screen::~Screen()
{
    if (mPixelFormat)
    {
        SDL_FreeFormat(mPixelFormat);
        mPixelFormat = nullptr;
    }
    if (mTexture)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
    }
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag, bool fast)
{
    mFast = fast;
    mWidth = w;
    mHeight = h;

    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "Failed to Init SDL2" << std::endl;
        return nullptr;
    }

    mWindow = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth * mag, mHeight * mag, 0);
    if (mWindow)
    {
        uint8_t rClear = 0;
        uint8_t gClear = 0;
        uint8_t bClear = 0;
        uint8_t aClear = 255;
        if (mFast)
        {
            mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
            if (!mRenderer)
            {
                std::cout << "Failed to initialize renderer" << std::endl;
                mFast = false;
            }
            else
            {
                SDL_SetRenderDrawColor(mRenderer, rClear, gClear, bClear, aClear);
                mPixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
                mTexture = SDL_CreateTexture(mRenderer, mPixelFormat->format, SDL_TEXTUREACCESS_STREAMING, mWidth, mHeight);
            }
        }
        if (!mFast)
        {
            mSurface = SDL_GetWindowSurface(mWindow);
            mPixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        }

        mBackBuffer.Init(mPixelFormat->format, mWidth, mHeight);
        Color::InitColorFormat(mPixelFormat);
        mClearColor = Color(rClear, gClear, bClear, aClear);
        mBackBuffer.Clear(mClearColor);
    }

    return mWindow;
}

void Screen::SetRenderColor(const Color &color)
{
    if (mRenderer == nullptr)
    {
        return;
    }
    mClearColor = color;
    int val = SDL_SetRenderDrawColor(mRenderer, mClearColor.GetRed(), mClearColor.GetGreen(), mClearColor.GetBlue(), mClearColor.GetAlpha());

    std::cout << val << std::endl;
}

void Screen::SwapScreen()
{
    if (mWindow)
    {
        ClearScreen();

        if (mFast)
        {
            uint8_t *textureData = nullptr;
            int texturePitch = 0;
            if (SDL_LockTexture(mTexture, nullptr, (void **)&textureData, &texturePitch) >= 0)
            {
                SDL_Surface *surface = mBackBuffer.GetSurface();
                memcpy(textureData, surface->pixels, surface->w * surface->h * mPixelFormat->BytesPerPixel);
                SDL_UnlockTexture(mTexture);
                SDL_RenderCopy(mRenderer, mTexture, nullptr, nullptr);
                SDL_RenderPresent(mRenderer);
            }
        }
        else
        {
            SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mSurface, nullptr);
            SDL_UpdateWindowSurface(mWindow);
        }

        mBackBuffer.Clear(mClearColor);
    }
}

void Screen::ClearScreen()
{
    if (mWindow)
    {
        if (mFast)
        {
            SDL_RenderClear(mRenderer);
        }
        else
        {
            SDL_FillRect(mSurface, nullptr, mClearColor.GetPixelColor());
        }
    }
}
// draw methods below
void Screen::Draw(int x, int y, const Color &color)
{
    if (mWindow)
    {
        mBackBuffer.SetPixel(color, x, y);
    }
}
void Screen::Draw(const Vec2D &point, const Color &color)
{
    if (mWindow)
    {
        mBackBuffer.SetPixel(color, point.GetX(), point.GetY());
    }
}

void Screen::Draw(const Line2D &line, const Color &color)
{

    if (mWindow)
    {
        int dx;
        int dy;

        int x0 = roundf(line.GetP0().GetX());
        int y0 = roundf(line.GetP0().GetY());
        int x1 = roundf(line.GetP1().GetX());
        int y1 = roundf(line.GetP1().GetY());

        dx = x1 - x0;
        dy = y1 - y0;

        signed const char ix((dx > 0) - (dx < 0));
        signed const char iy((dy > 0) - (dy < 0));

        dx = abs(dx) * 2;
        dy = abs(dy) * 2;

        Draw(x0, y0, color);

        if (dx >= dy)
        {
            int d = dy - dx / 2;
            while (x0 != x1)
            {
                if (d >= 0)
                {
                    d -= dx;
                    y0 += iy;
                }
                d += dy;
                x0 += ix;
                Draw(x0, y0, color);
            }
        }
        else
        {
            int d = dx - dy / 2;
            while (y0 != y1)
            {
                if (d >= 0)
                {
                    d -= dy;
                    x0 += ix;
                }
                d += dx;
                y0 += iy;
                Draw(x0, y0, color);
            }
        }
    }
}

void Screen::Draw(Triangle &triangle, const Color &color, bool fill, const Color &fillColor)
{
    if (fill)
    {
        FillPoly(triangle.GetPoints(), [fillColor](uint32_t x, uint32_t y)
                 { return fillColor; });
    }
    Draw(Line2D(triangle.GetP0(), triangle.GetP1()), color);
    Draw(Line2D(triangle.GetP1(), triangle.GetP2()), color);
    Draw(Line2D(triangle.GetP2(), triangle.GetP0()), color);
}

void Screen::Draw(AARectangle &rect, const Color &color, bool fill, const Color &fillColor)
{
    if (fill)
    {
        FillPoly(rect.GetPoints(), [fillColor](uint32_t x, uint32_t y)
                 { return fillColor; });
    }
    std::vector<Vec2D> points = rect.GetPoints();
    Draw(Line2D(points[0], points[1]), color);
    Draw(Line2D(points[1], points[2]), color);
    Draw(Line2D(points[2], points[3]), color);
    Draw(Line2D(points[3], points[0]), color);
}

void Screen::Draw(Circle &circle, const Color &color, bool fill, const Color &fillColor)
{
    std::vector<Vec2D> points;
    std::vector<Line2D> lines;
    unsigned int NUM_CIRCLE_SEGS = 30;
    if (circle.GetRadius() < 10)
    {
        NUM_CIRCLE_SEGS = 16;
    }
    else if (circle.GetRadius() < 5)
    {
        NUM_CIRCLE_SEGS = 8;
    }
    float angle = TWO_PI / float(NUM_CIRCLE_SEGS);

    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    p0.Rotate(angle, circle.GetCenterPoint());
    Vec2D p1 = p0;
    Line2D nextLine;
    // points.push_back(p0);
    for (unsigned int i = 0; i < NUM_CIRCLE_SEGS; ++i)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        nextLine.SetP0(p0);
        nextLine.SetP1(p1);
        lines.push_back(nextLine);
        p0 = p1;
        points.push_back(p0);
    }

    for (const Line2D &line : lines)
    {
        Draw(line, color);
    }

    if (fill)
    {
        FillPoly(points, [fillColor](uint32_t x, uint32_t y)
                 { return fillColor; });
    }
}

void Screen::Draw(BMPImage &image, Sprite &sprite, Vec2D &pos, const Color &overlayColor, float mag)
{
    uint32_t width = sprite.width;
    uint32_t height = sprite.height;

    float rVal = CreateOverlayValue(overlayColor.GetRed());
    float gVal = CreateOverlayValue(overlayColor.GetGreen());
    float bVal = CreateOverlayValue(overlayColor.GetBlue());
    float aVal = CreateOverlayValue(overlayColor.GetAlpha());

    const std::vector<Color> &pixels = image.GetPixels();
    Vec2D topLeft = pos;
    Vec2D topRight = pos + Vec2D(width * mag, 0);
    Vec2D bottomLeft = pos + Vec2D(0, height * mag);
    Vec2D bottomRight = pos + Vec2D(width * mag, height * mag);

    std::vector<Vec2D> points = {topLeft, bottomLeft, bottomRight, topRight};
    Vec2D xAxis = topRight - topLeft;
    Vec2D yAxis = bottomLeft - topLeft;

    const float invXAxisLenSq = 1.0f / xAxis.Mag2();
    const float invYAxisLenSq = 1.0f / yAxis.Mag2();

    FillPoly(points, [&](uint32_t px, uint32_t py)
             { Vec2D p(px, py);
        Vec2D d = p - topLeft;
        float u = invXAxisLenSq * d.Dot(xAxis);
        float v = invYAxisLenSq * d.Dot(yAxis);
        
        u = Clamp(u, 0.0f, 1.0f);
        v = Clamp(v, 0.0f, 1.0f);

        float tx = roundf(u * static_cast<float>(sprite.width));
        float ty = roundf(v * static_cast<float>(sprite.height));

        Color pixelColor = image.GetPixels()[GetIndex(image.GetWidth(), ty + sprite.yPos, tx + sprite.xPos)];
        Color newPixelColor = {static_cast<uint8_t>(pixelColor.GetRed() * rVal), static_cast<uint8_t>(pixelColor.GetGreen() * gVal), static_cast<uint8_t>(pixelColor.GetBlue() * bVal), static_cast<uint8_t>(pixelColor.GetAlpha() * aVal)};

        return newPixelColor; });
}

void Screen::Draw(SpriteSheet &ss, const std::string &spriteName, Vec2D &pos, const Color &overlayColor, float mag)
{
    Sprite sprite = ss.GetSprite(spriteName);
    Draw(ss.GetBMPImage(), sprite, pos, overlayColor, mag);
}

void Screen::Draw(BitmapFont &font, const std::string &text, Vec2D &pos, const Color &overlayColor, float mag)
{
    uint32_t xPos = pos.GetX();
    SpriteSheet &ss = font.GetFontSheet();

    for (char c : text)
    {
        if (c == ' ')
        {
            xPos += font.GetFontSpacingBetweenWords();
            continue;
        }
        Sprite sprite = ss.GetSprite(std::string("") + c);
        Vec2D newPos(xPos, pos.GetY());
        Draw(ss.GetBMPImage(), sprite, newPos, overlayColor, mag);
        xPos += sprite.width;
        xPos += font.GetFontSpacingBetweenLetters();
    }
}

void Screen::FillPoly(const std::vector<Vec2D> &points, FillPolyFunc func)
{
    if (points.size() > 0)
    {
        float top = points[0].GetY();
        float right = points[0].GetX();
        float bottom = points[0].GetY();
        float left = points[0].GetX();

        for (size_t i = 1; i < points.size(); ++i)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }
            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }
            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }
        }

        for (int pixelY = top; pixelY < bottom; ++pixelY)
        {
            std::vector<float> nodeXVec;
            size_t j = points.size() - 1;

            for (size_t i = 0; i < points.size(); ++i)
            {
                float pointiY = points[i].GetY();
                float pointjY = points[j].GetY();

                // WTF??
                if ((pointiY <= (float)pixelY && pointjY > (float)pixelY) || (pointjY <= pixelY && pointiY > pixelY))
                {
                    float denom = pointjY - pointiY;
                    if (IsEqual(denom, 0))
                    {
                        continue;
                    }
                    float x = points[i].GetX() + (pixelY - pointiY) / (denom) * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }
                j = i;
            }

            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

            for (size_t k = 0; k < nodeXVec.size(); k += 2)
            {
                if (nodeXVec[k] > right)
                {
                    break;
                }
                if (nodeXVec[k + 1] > left)
                {
                    if (nodeXVec[k] < left)
                    {
                        nodeXVec[k] = left;
                    }
                    if (nodeXVec[k + 1] > right)
                    {
                        nodeXVec[k + 1] = right;
                    }
                    for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; ++pixelX)
                    {
                        Draw(pixelX, pixelY, func(pixelX, pixelY));
                    }
                }
            }
        }
    }
}