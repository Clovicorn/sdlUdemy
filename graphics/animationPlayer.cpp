#include "animationPlayer.hpp"

AnimationPlayer::AnimationPlayer() : mTime(0), mCurAnimation(0), mFrame(0), mLooped(false), mIsPlaying(false), mIsFinishedPlaying(false)
{
}

bool AnimationPlayer::Init(const std::string &filePath)
{
    mAnimations = Animation::LoadAnimations(filePath);

    return mAnimations.size() > 0;
}

bool AnimationPlayer::Play(const std::string &animationName, bool looped)
{
    bool found = false;
    for (size_t i = 0; i < mAnimations.size(); i++)
    {
        if (mAnimations[i].GetAnimationName() == animationName)
        {
            mCurAnimation = i;
            found = true;
            break;
        }
    }
    if (found)
    {
        mIsPlaying = true;
        mFrame = 0;
        mTime = 0;
        mLooped = looped;
        mIsFinishedPlaying = false;
    }

    return found;
}

void AnimationPlayer::Pause()
{
    if (mIsFinishedPlaying)
    {
        mIsPlaying = !mIsPlaying;
    }
}

void AnimationPlayer::Stop()
{
    mIsPlaying = false;
    mTime = 0;
    mFrame = 0;
    mIsFinishedPlaying = true;
}

void AnimationPlayer::Update(uint32_t dt)
{
    if (mIsPlaying)
    {
        mTime += dt;

        int fps = mAnimations[mCurAnimation].GetFPS();

        float msPerFrame = static_cast<float>(1000) / static_cast<float>(fps);

        if (static_cast<float>(mTime) > msPerFrame)
        {
            mTime -= static_cast<uint32_t>(msPerFrame);
            if (mFrame + 1 < mAnimations[mCurAnimation].NumFrames())
            {
                mFrame++;
            }
            else if ((mFrame + 1 >= mAnimations[mCurAnimation].NumFrames()) && mLooped)
            {
                mFrame = 0;
            }
            else
            {
                mIsFinishedPlaying = true;
            }
        }
    }
}

AnimationFrame AnimationPlayer::GetCurrentAnimationFrame() const
{
    if (mAnimations.empty())
    {
        return AnimationFrame();
    }

    return mAnimations[mCurAnimation].GetAnimationFrame(GetCurrentFrameNumber());
}
