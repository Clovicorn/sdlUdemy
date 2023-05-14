#include "bmpImage.hpp"

BMPImage::BMPImage() : mWidth(0), mHeight(0)
{
}

bool BMPImage::Load(const std::string &path)
{
    SDL_Surface *bmpSurface = SDL_LoadBMP(path.c_str());
    if (bmpSurface == nullptr)
    {
        return false;
    }

    mWidth = bmpSurface->w;
    mHeight = bmpSurface->h;

    size_t lengthOfPixels = mWidth * mHeight;
    mPixels.reserve(lengthOfPixels);

    SDL_LockSurface(bmpSurface);
    uint32_t *pixels = static_cast<uint32_t *>(bmpSurface->pixels);
    for (uint32_t i = 0; i < lengthOfPixels; i++)
    {
        mPixels.push_back(Color(pixels[i]));
    }
    SDL_UnlockSurface(bmpSurface);
    SDL_FreeSurface(bmpSurface);
    return true;
}