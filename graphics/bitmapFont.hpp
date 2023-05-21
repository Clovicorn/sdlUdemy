#ifndef GRAPHICS_BITMAP_FONT_H_
#define GRAPHICS_BITMAP_FONT_H_

#include "spriteSheet.hpp"
#include <stdint.h>

class Vec2D;
class AARectangle;
struct Size;

enum FontXAlign
{
    BFXA_LEFT = 0,
    BFXA_CENTER,
    BFXA_RIGHT
};

enum FontYAlign
{
    BFYA_TOP = 0,
    BFYA_CENTER,
    BFYA_BOTTOM
};

class BitmapFont
{
public:
    BitmapFont() {}
    bool Load(const std::string &filePath);
    Size GetSizeOf(const std::string &str);
    Vec2D GetDrawPosition(const std::string &str, const AARectangle &box, FontXAlign xAlign = BFXA_LEFT, FontYAlign yAlign = BFYA_BOTTOM);
    inline const SpriteSheet &GetFontSheet() const { return mFontSheet; }
    inline const uint32_t GetFontSpacingBetweenLetters() const { return 2; }
    inline const uint32_t GetFontSpacingBetweenWords() const { return 5; }

private:
    SpriteSheet mFontSheet;
};

#endif /* GRAPHICS_BITMAP_FONT_H_ */