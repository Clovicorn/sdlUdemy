#include "highScores.hpp"
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include "../graphics/bitmapFont.hpp"
#include "../graphics/screen.hpp"
#include "../utils/fileCommandLoader.hpp"
#include "../shapes/aaRectangle.hpp"
#include "../app/app.hpp"

HighScores::HighScores()
{
}

HighScores::~HighScores()
{
}

void HighScores::Draw(Screen &screen)
{
    BitmapFont &font = App::Singleton().GetFont();
    if (mScoreState == SCORE_SHOW)
    {
        unsigned int height_11 = App::Singleton().Height() / 11;
        AARectangle rect(Vec2D::Zero, App::Singleton().Width(), height_11);
        Vec2D pos = font.GetDrawPosition(std::string("High Scores"), rect, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(font, std::string("High Scores"), pos, Color::Red());
        unsigned int height_12 = (App::Singleton().Height() - height_11) / 11;
        rect = {Vec2D(60, height_11 + 10), App::Singleton().Height(), height_12};
        for (size_t i = 0; i < mScores.size(); i++)
        {
            std::string nameAndScore = mScores[i].name + "    " + to_string(mScores[i].score);
            pos = font.GetDrawPosition(nameAndScore, rect, BFXA_LEFT, BFYA_CENTER);
            screen.Draw(font, nameAndScore, pos, Color::Cyan());
            rect.MoveBy(Vec2D(0, height_12));
        }
    }
    if (mScoreState == SCORE_UPDATE)
    {
        std::vector<std::string> spriteNames = font.GetFontSheet().GetSpriteNames();

        AARectangle rect(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() / 2);

        Vec2D pos = font.GetDrawPosition(std::string("Enter Initials:"), rect, BFXA_CENTER, BFYA_BOTTOM);

        screen.Draw(font, std::string("Enter Initials:"), pos, Color::Red());

        int startXPos = (App::Singleton().Width() / 2) - ((12 * 3) / 2);
        int startYPos = (App::Singleton().Height() / 2) + 5;

        AARectangle initialRect(Vec2D(startXPos, startYPos), 12, 12);
        pos = font.GetDrawPosition(spriteNames[mInitials[0]], initialRect, BFXA_CENTER, BFYA_TOP);
        Color color = mCurInitial == 0 ? Color::Cyan() : Color::White();
        screen.Draw(font, spriteNames[mInitials[0]], pos, color);

        initialRect.MoveBy(Vec2D(initialRect.GetWidth() + 1, 0));
        pos = font.GetDrawPosition(spriteNames[mInitials[1]], initialRect, BFXA_CENTER, BFYA_TOP);
        color = mCurInitial == 1 ? Color::Cyan() : Color::White();
        screen.Draw(font, spriteNames[mInitials[1]], pos, color);

        initialRect.MoveBy(Vec2D(initialRect.GetWidth() + 1, 0));
        pos = font.GetDrawPosition(spriteNames[mInitials[2]], initialRect, BFXA_CENTER, BFYA_TOP);
        color = mCurInitial == 2 ? Color::Cyan() : Color::White();
        screen.Draw(font, spriteNames[mInitials[2]], pos, color);
    }
}

void HighScores::Init(const std::string &pathToFile)
{
    mScoreState = SCORE_SHOW;
    mTimeElapsed = 0;
    mCurInitial = 0;
    mPathAndFileName = pathToFile;
    LoadScoreFile(pathToFile);
}

bool HighScores::Update(uint32_t dt)
{
    if (mScoreState == SCORE_SHOW)
    {
        if (mTimeElapsed == 300)
        {
            mTimeElapsed = 0;
            return false;
        }
        else
        {
            mTimeElapsed += 1;
        }
    }
    return true;
}

bool HighScores::CheckScore(int score)
{
    for (auto &nameScore : mScores)
    {
        if (score >= nameScore.score)
        {
            return true;
        }
    }
    return false;
}

void HighScores::LoadScoreFile(const std::string &filePath)
{
    FileCommandLoader loader;

    Command nameCommand;
    nameCommand.command = "name";
    nameCommand.parseFunc = [this](ParseParams params)
    {
        NameScore newNameScore;
        newNameScore.name = FileCommandLoader::ReadString(params);
        mScores.push_back(newNameScore);
    };

    Command scoreCommand;
    scoreCommand.command = "score";
    scoreCommand.parseFunc = [this](ParseParams params)
    {
        mScores.back().score = FileCommandLoader::ReadInt(params);
    };

    loader.AddCommand(nameCommand);
    loader.AddCommand(scoreCommand);

    loader.LoadFile(filePath);
}

bool compareScore(NameScore s1, NameScore s2)
{
    return (s1.score > s2.score);
}

void HighScores::AddScore(const NameScore &name)
{
    mScores.back() = name;

    std::sort(mScores.begin(), mScores.end(), compareScore);
    SaveScores();
}

void HighScores::SetPreviousLetter()
{
    BitmapFont &font = App::Singleton().GetFont();
    mInitials[mCurInitial]--;
    if (mInitials[mCurInitial] < 0)
    {
        mInitials[mCurInitial] = font.GetFontSheet().GetSpriteNames().size() - 1;
    }
}

void HighScores::SetNextLetter()
{
    BitmapFont &font = App::Singleton().GetFont();
    mInitials[mCurInitial] = (mInitials[mCurInitial] + 1) % font.GetFontSheet().GetSpriteNames().size();
}

void HighScores::AcceptName(int score)
{
    BitmapFont &font = App::Singleton().GetFont();
    std::vector<std::string> spriteNames = font.GetFontSheet().GetSpriteNames();
    NameScore nameScore;
    nameScore.name = spriteNames[mInitials[0]] + spriteNames[mInitials[1]] + spriteNames[mInitials[2]];
    nameScore.score = score;
    AddScore(nameScore);
    mScoreState = SCORE_SHOW;
}

void HighScores::MoveLeft()
{
    mCurInitial--;
    if (mCurInitial < 0)
    {
        mCurInitial = 2;
    }
}

void HighScores::MoveRight()
{
    mCurInitial = (mCurInitial + 1) % 3;
}

void HighScores::SaveScores()
{
    std::ofstream outputFile;
    outputFile.open(mPathAndFileName, ios::out | ios::trunc);
    if (!outputFile.is_open())
    {
        std::cout << "failed to open file" << std::endl;
    }
    if (outputFile.is_open())
    {
        for (size_t i = 0; i < mScores.size(); i++)
        {
            std::string name = ":name " + mScores[i].name + "\n";
            std::string score = ":score " + std::to_string(mScores[i].score) + "\n\n";
            outputFile << name;
            outputFile << score;
        }
        outputFile.close();
    }
}