#include "fileCommandLoader.hpp"

void FileCommandLoader::AddCommand(const Command &command)
{
    mCommands.push_back(command);
}

bool FileCommandLoader::LoadFile(std::string &filePath)
{
    std::ifstream inFile;
    std::string line = "";

    inFile.open(filePath);
    if (!inFile.is_open())
    {
        std::cout << "Faild to open file: " << filePath << std::endl;
        return false;
    }

    while (!inFile.eof())
    {
        std::getline(inFile, line);
        size_t commandPos = std::string::npos;
        if ((commandPos = line.find(":")) != std::string::npos)
        {
            size_t delimitPos = line.find_first_of(" ");
            if (delimitPos == std::string::npos)
            {
                delimitPos = line.length();
            }
            else
            {
                delimitPos -= 1;
            }

            std::string commandStr = line.substr(commandPos + 1, delimitPos);
            delimitPos += 1;

            for (size_t index = 0; index < mCommands.size(); index++)
            {
                if (commandStr == mCommands[index].command)
                {
                    if (mCommands[index].commandType == COMMAND_ONE_LINE)
                    {
                        ParseParams params;
                        params.delimitPos = delimitPos;
                        params.line = line;
                        params.lineNum = 0;
                        mCommands[index].parseFunc(params);
                    }
                    else
                    {
                        std::string numLines = line.substr(delimitPos + 1);
                        size_t totalLines = std::stoi(numLines);
                        int lineNum = 0;
                        while (lineNum < totalLines)
                        {
                            std::getline(inFile, line);
                            if (line.empty())
                            {
                                continue;
                            }
                            else
                            {
                                ParseParams params;
                                params.delimitPos = 0;
                                params.lineNum = lineNum;
                                params.line = line;
                                mCommands[index].parseFunc(params);
                                lineNum++;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

Color FileCommandLoader::ReadColor(const ParseParams &params)
{
    size_t nextSpacePos = params.line.find_first_of(" ", params.delimitPos + 1);
    int r = std::stoi(params.line.substr(params.delimitPos, (nextSpacePos - params.delimitPos)));

    size_t lastSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
    int g = std::stoi(params.line.substr(lastSpacePos + 1, (nextSpacePos - lastSpacePos)));

    lastSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
    int b = std::stoi(params.line.substr(lastSpacePos, (nextSpacePos - lastSpacePos)));

    int a = std::stoi(params.line.substr(nextSpacePos + 1));

    return Color(r, g, b, a);
}

Vec2D FileCommandLoader::ReadSize(const ParseParams &params)
{
    size_t nextSpacePos = params.line.find_first_of(" ", params.delimitPos + 1);
    int width = std::stoi(params.line.substr(params.delimitPos + 1, (nextSpacePos - params.delimitPos)));

    size_t lastSpacePos = nextSpacePos;
    nextSpacePos = params.line.find_first_of(" ", nextSpacePos + 1);
    int height = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

    return Vec2D(width, height);
}

int FileCommandLoader::ReadInt(const ParseParams &params)
{
    std::string intStr = params.line.substr(params.delimitPos + 1);
    return std::stoi(intStr);
}

std::string FileCommandLoader::ReadString(const ParseParams &params)
{
    return params.line.substr(params.delimitPos + 1);
}

char FileCommandLoader::ReadChar(const ParseParams &params)
{
    return params.line.substr(params.delimitPos + 1)[0];
}