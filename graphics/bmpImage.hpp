#ifndef GRAPHICS_BMPIMAGE_H_
#define GRAPHICS_BMPIMAGE_H_

#include <stdint.h>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "color.hpp"

class BMPImage
{
public:
    BMPImage();
    bool Load(const std::string &path);

    inline const std::vector<Color> &GetPixels() const { return mPixels; }
    inline const uint32_t GetWidth() const { return mWidth; }
    inline const uint32_t GetHeight() const { return mHeight; }

private:
    std::vector<Color> mPixels;
    uint32_t mWidth;
    uint32_t mHeight;
};

#endif /* GRAPHICS_BMPIMAGE_H_ */