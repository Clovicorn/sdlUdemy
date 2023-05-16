#ifndef GRAPHICS_SPRITESHEET_H_
#define GRAPHICS_SPRITESHEET_H_

#include <stdint.h>
#include <string>
#include <vector>

#include "bmpImage.hpp"
#include "../utils/utils.hpp"

class FileCommandLoader;

struct Sprite
{
    uint32_t xPos = 0;
    uint32_t yPos = 0;
    uint32_t width = 0;
    uint32_t height = 0;
};

class SpriteSheet
{
public:
    SpriteSheet();
    bool Load(const std::string &name);
    Sprite GetSprite(const std::string &spriteName) const;

    std::vector<std::string> GetSpriteNames() const;

    inline BMPImage &GetBMPImage() { return mBMPImage; }
    inline uint32_t GetWidth() { return mBMPImage.GetWidth(); }
    inline uint32_t GetHeight() { return mBMPImage.GetHeight(); }

private:
    bool LoadSpriteSections(const std::string path);
    struct BMPImageSection
    {
        std::string key = "";
        Sprite sprite;
    };

    BMPImage mBMPImage;
    std::vector<BMPImageSection> mSections;
};

#endif /* GRAPHICS_SPRITESHEET_H_ */