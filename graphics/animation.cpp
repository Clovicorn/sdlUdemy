#include "animation.hpp"
#include "../utils/fileCommandLoader.hpp"

Animation::Animation() : mSpriteSheetName(""), mAnimationName(""), mFPS(0)
{
}

AnimationFrame Animation::GetAnimationFrame(uint32_t frameNum) const
{
    AnimationFrame frame;

    if (frameNum > mFrames.size())
    {
        return frame;
    }

    frame.frame = mFrames[frameNum];
    if (frameNum < mFrameColors.size())
    {
        frame.frameColor = mFrameColors[frameNum];
        frame.frameColorSet = true;
    }

    if (frameNum < mFrameOffsets.size())
    {
        frame.offset = mFrameOffsets[frameNum];
    }

    if (mOverlay.size() > 0)
    {
        frame.overlay = mOverlay;
    }
    if (frameNum < mOverlayColors.size())
    {
        frame.overlayColor = mOverlayColors[frameNum];
    }

    frame.size = mSize;

    return frame;
}

std::vector<Animation> Animation::LoadAnimations(const std::string &filePath)
{
    std::vector<Animation> animations;
    FileCommandLoader loader;

    Command animationCommand;
    animationCommand.command = "animation";
    animationCommand.parseFunc = [&](ParseParams params)
    {
        Animation newAnimation;
        newAnimation.SetAnimationName(FileCommandLoader::ReadString(params));
        animations.push_back(newAnimation);
    };

    Command spriteSheetCommand;
    spriteSheetCommand.command = "sprite_sheet";
    spriteSheetCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().SetSpriteSheetName(FileCommandLoader::ReadString(params));
    };

    Command sizeCommand;
    sizeCommand.command = "size";
    sizeCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().SetSize(FileCommandLoader::ReadSize(params));
    };

    Command fpsCommand;
    fpsCommand.command = "fps";
    fpsCommand.parseFunc = [&](ParseParams params)
    {
        std::cout << "trying to read fps" << std::endl;
        animations.back().SetFPS(FileCommandLoader::ReadInt(params));
        std::cout << "fps read" << std::endl;
    };

    Command framesCommand;
    framesCommand.command = "frame_keys";
    framesCommand.commandType = COMMAND_MULTI_LINE;
    framesCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().AddFrameName(params.line);
    };

    Command overlayCommand;
    overlayCommand.command = "overlay";
    overlayCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().SetOverlayName(FileCommandLoader::ReadString(params));
    };

    Command frameColorsCommand;
    frameColorsCommand.command = "frame_colors";
    frameColorsCommand.commandType = COMMAND_MULTI_LINE;
    frameColorsCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().AddFrameColor(FileCommandLoader::ReadColor(params));
    };

    Command overlayColorsCommand;
    overlayColorsCommand.command = "overlay_colors";
    overlayColorsCommand.commandType = COMMAND_MULTI_LINE;
    overlayColorsCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().AddOverlayColor(FileCommandLoader::ReadColor(params));
    };

    Command offsetsCommand;
    offsetsCommand.command = "frame_offsets";
    offsetsCommand.commandType = COMMAND_MULTI_LINE;
    offsetsCommand.parseFunc = [&](ParseParams params)
    {
        animations.back().AddFrameOffset(FileCommandLoader::ReadSize(params));
    };

    loader.AddCommand(animationCommand);
    loader.AddCommand(spriteSheetCommand);
    loader.AddCommand(sizeCommand);
    loader.AddCommand(fpsCommand);
    loader.AddCommand(framesCommand);
    loader.AddCommand(overlayCommand);
    loader.AddCommand(frameColorsCommand);
    loader.AddCommand(overlayColorsCommand);
    loader.AddCommand(offsetsCommand);

    loader.LoadFile(filePath);
    return animations;
}