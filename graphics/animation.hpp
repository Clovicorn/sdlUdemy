#ifndef GRAPHICS_ANIMATION_H
#define GRAPHICS_ANIMATION_H

#include <string>
#include <vector>

#include "color.hpp"
#include "../utils/utils.hpp"
#include "../utils/vec2d.hpp"

struct AnimationFrame
{
    std::string frame = "";
    std::string overlay = "";
    Color frameColor = Color::White();
    Color overlayColor = Color::White();
    Vec2D size;
    Vec2D offset = Vec2D::Zero;
    bool frameColorSet = false;
};

class Animation
{
public:
    Animation();
    AnimationFrame GetAnimationFrame(uint32_t frame) const;
    void AddFrameName(const std::string &name) { mFrames.push_back(name); }
    void AddFrameColor(const Color &color) { mFrameColors.push_back(color); }
    void AddOverlayColor(const Color &color) { mOverlayColors.push_back(color); }
    void AddFrameOffset(const Vec2D &offset) { mFrameOffsets.push_back(offset); }

    void SetAnimationName(const std::string &name) { mAnimationName = name; }
    const std::string &GetAnimationName() const { return mAnimationName; }

    void SetSpriteSheetName(const std::string &spriteSheetName) { mSpriteSheetName = spriteSheetName; }
    const std::string &GetSpriteSheetName() const { return mSpriteSheetName; }

    void SetOverlayName(const std::string &overlayName) { mOverlay = overlayName; }
    const std::string &GetOverlayName() const { return mOverlay; }

    void SetSize(const Vec2D &size) { mSize = size; }
    Vec2D GetSize() const { return mSize; }

    void SetFPS(int fps) { mFPS = fps; }
    int GetFPS() { return mFPS; }

    size_t NumFrameColors() { return mFrameColors.size(); }
    size_t NumOverlayColors() { return mOverlayColors.size(); }
    size_t NumFrameOffsets() { return mFrameOffsets.size(); }
    size_t NumFrames() { return mFrames.size(); }

    static std::vector<Animation> LoadAnimations(const std::string &filePath);

private:
    std::string mAnimationName = "";
    std::string mSpriteSheetName = "";
    std::string mOverlay = "";
    std::vector<std::string> mFrames;
    std::vector<Color> mFrameColors;
    std::vector<Color> mOverlayColors;
    std::vector<Vec2D> mFrameOffsets;
    Vec2D mSize;
    int mFPS;
};
#endif /* GRAPHICS_ANIMATION_H */