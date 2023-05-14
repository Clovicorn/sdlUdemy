#ifndef FILE_COMMAND_LOADER_H
#define FILE_COMMAND_LOADER_H

#include <functional>
#include <fstream>
#include <string>
#include <vector>

class Vec2D;
class Color;

enum CommandType
{
    COMMAND_ONE_LINE = 0,
    COMMAND_MULTI_LINE
};
struct ParseParams
{
    std::string line;
    uint32_t delimitPos;
    uint32_t lineNum;
};
using ParseFunc = std::function<void(const ParseParams &parseFuncParams)>;

struct Command
{
    CommandType commandType = COMMAND_ONE_LINE;
    std::string command = "";
    ParseFunc parseFunc = nullptr;
};

class FileCommandLoader
{
public:
    void AddCommand(const Command &command);
    bool LoadFile(const std::string &filePath);

    static Color ReadColor(const ParseParams &params);
    static Vec2D ReadSize(const ParseParams &params);
    static int ReadInt(const ParseParams &params);
    static std::string ReadString(const ParseParams &params);
    static char ReadChar(const ParseParams &params);

private:
    std::vector<Command> mCommands;
};

#endif /* FILE_COMMAND_LOADER_H */