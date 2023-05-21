#ifndef GRAPHICS_ANIMATION_PLAYER_H
#define GRAPHICS_ANIMATION_PLAYER_H

#include <stdint.h>
#include <vector>

#include "animation.hpp"

class AnimationPlayer
{
public:
    AnimationPlayer();
    bool Init(const std::string &filePath);
    bool Play(const std::string &animationName, bool looped);
    void Pause();
    void Stop();
    void Update(uint32_t dt);
    AnimationFrame GetCurrentAnimationFrame() const;

    inline bool IsFinishedPlaying() const { return mIsFinishedPlaying; }
    inline uint32_t GetCurrentFrameNumber() const { return mFrame; }

private:
    uint32_t mTime;
    std::vector<Animation> mAnimations;
    size_t mCurAnimation;
    uint32_t mFrame;

    bool mLooped;
    bool mIsPlaying;
    bool mIsFinishedPlaying;
};

#endif /* GRAPHICS_ANIMATION_PLAYER_H */