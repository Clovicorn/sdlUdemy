#include "spriteSheet.hpp"
#include "../utils/fileCommandLoader.hpp"
#include "../app/app.hpp"

SpriteSheet::SpriteSheet()
{
}

bool SpriteSheet::Load(const std::string &name)
{
    std::string bmpName = App::Singleton().GetBasePath() + "assets/" + name + ".bmp";
    std::string txtName = App::Singleton().GetBasePath() + "assets/" + name + ".txt";

    bool loadBMPImage = mBMPImage.Load(bmpName);
    if (!loadBMPImage)
    {
        std::cout << "Failed to load BMP image in SpriteSheet" << std::endl;
    }
    bool loadSpriteSection = LoadSpriteSections(txtName);
    if (!loadSpriteSection)
    {
        std::cout << "Failed to load Sprite sections in SpriteSheet" << std::endl;
    }
    return loadBMPImage && loadSpriteSection;
}

Sprite SpriteSheet::GetSprite(const std::string &spriteName) const
{
    for (auto &spriteSection : mSections)
    {
        if (StringCompare(spriteName, spriteSection.key))
        {
            return spriteSection.sprite;
        }
    }
    return Sprite();
}
std::vector<std::string> SpriteSheet::GetSpriteNames() const
{
    size_t length = mSections.size();
    std::vector<std::string> names;
    for (size_t i = 0; i < length; i++)
    {
        names.push_back(mSections[i].key);
    }

    return names;
}

bool SpriteSheet::LoadSpriteSections(const std::string path)
{

    FileCommandLoader loader;

    Command spriteCommand;
    spriteCommand.command = "sprite";
    spriteCommand.parseFunc = [&](ParseParams params)
    {
        BMPImageSection section;
        mSections.push_back(section);
    };
    Command keyCommand;
    keyCommand.command = "key";
    keyCommand.parseFunc = [&](ParseParams params)
    {
        std::string key = FileCommandLoader::ReadString(params);
        mSections.back().key = key;
    };

    Command xPosCommand;
    xPosCommand.command = "xPos";
    xPosCommand.parseFunc = [&](ParseParams params)
    {
        uint32_t xPos = static_cast<uint32_t>(FileCommandLoader::ReadInt(params));
        mSections.back().sprite.xPos = xPos;
    };

    Command yPosCommand;
    yPosCommand.command = "yPos";
    yPosCommand.parseFunc = [&](ParseParams params)
    {
        uint32_t yPos = static_cast<uint32_t>(FileCommandLoader::ReadInt(params));
        mSections.back().sprite.yPos = yPos;
    };

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseParams params)
    {
        uint32_t width = static_cast<uint32_t>(FileCommandLoader::ReadInt(params));
        mSections.back().sprite.width = width;
    };

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseParams params)
    {
        uint32_t height = static_cast<uint32_t>(FileCommandLoader::ReadInt(params));
        mSections.back().sprite.height = height;
    };

    loader.AddCommand(spriteCommand);
    loader.AddCommand(keyCommand);
    loader.AddCommand(xPosCommand);
    loader.AddCommand(yPosCommand);
    loader.AddCommand(widthCommand);
    loader.AddCommand(heightCommand);

    return loader.LoadFile(path);
}
