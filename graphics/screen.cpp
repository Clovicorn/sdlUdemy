#include "screen.hpp"

Screen::Screen() : mWindow(nullptr), mSurface(nullptr), mWidth(0), mHeight(0)
{
}
Screen::~Screen()
{
    if (mWindow)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    SDL_Quit();
}

SDL_Window *Screen::Init(uint32_t w, uint32_t h, uint32_t mag)
{
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

        mSurface = SDL_GetWindowSurface(mWindow);
        mBackBuffer.Init(mSurface->format->format, mWidth, mHeight);
        Color::InitColorFormat(mBackBuffer.GetSurface()->format);
        mClearColor = Color::Black();
        mBackBuffer.Clear(mClearColor);
    }

    return mWindow;
}

void Screen::SwapScreen()
{
    if (mWindow)
    {
        ClearScreen();
        SDL_BlitScaled(mBackBuffer.GetSurface(), nullptr, mSurface, nullptr);
        SDL_UpdateWindowSurface(mWindow);
        mBackBuffer.Clear(mClearColor);
    }
}

void Screen::ClearScreen()
{
    if (mWindow)
    {
        SDL_FillRect(mSurface, nullptr, mClearColor.GetPixelColor());
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
        FillPoly(triangle.GetPoints(), fillColor);
    }
    Draw(Line2D(triangle.GetP0(), triangle.GetP1()), color);
    Draw(Line2D(triangle.GetP1(), triangle.GetP2()), color);
    Draw(Line2D(triangle.GetP2(), triangle.GetP0()), color);
}

void Screen::Draw(AARectangle &rect, const Color &color, bool fill, const Color &fillColor)
{
    if (fill)
    {
        FillPoly(rect.GetPoints(), fillColor);
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
    static unsigned int NUM_CIRCLE_SEGS = 30;
    float angle = TWO_PI / float(NUM_CIRCLE_SEGS);

    Vec2D p0 = Vec2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vec2D p1 = p0;
    for (unsigned int i = 0; i < NUM_CIRCLE_SEGS; ++i)
    {
        p1.Rotate(angle, circle.GetCenterPoint());
        lines.push_back(Line2D(p1, p0));
        p0 = p1;
        points.push_back(p0);
    }

    if (fill)
    {
        FillPoly(points, fillColor);
    }
    for (const Line2D line : lines)
    {
        Draw(line, color);
    }
}

void Screen::FillPoly(const std::vector<Vec2D> &points, const Color &color)
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
                    float x = points[i].GetX() + (pixelY - pointiY) / denom * (points[j].GetX() - points[i].GetX());
                    nodeXVec.push_back(x);
                }
                j = i;
            }

            std::sort(nodeXVec.begin(), nodeXVec.end(), std::less<>());

            for (size_t k = 0; k < nodeXVec.size(); k += 2)
            {
                if (k > right)
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
                    for (int pixelX = nodeXVec[k]; pixelX < nodeXVec[k + 1]; pixelX++)
                    {
                        Draw(Vec2D(pixelX, pixelY), color);
                    }
                }
            }
        }
    }
}