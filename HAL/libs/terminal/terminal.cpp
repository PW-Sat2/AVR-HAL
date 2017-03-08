#include <string.h>
#include <cstdio>
#include "terminal.h"

static void parseCommandLine(char line[],
    char** commandName,
    char** arguments,
    uint16_t* argc,
    uint8_t maxArgsCount //
    )
{
    *argc = 0;

    char* ptr;
    char* token = strtok_r(line, " ", &ptr);

    *commandName = token;

    token = strtok_r(NULL, " ", &ptr);

    while (token != NULL && *argc < maxArgsCount)
    {
        arguments[*argc] = token;
        (*argc)++;

        token = strtok_r(NULL, " ", &ptr);
    }
}

void Terminal::HandleCommand(char* buffer)
{
    char* commandName;
    uint16_t argc = 0;
    char* args[8] = {0};

    parseCommandLine(buffer, &commandName, args, &argc, 8);

    for (auto& command : this->_commandList)
    {
        if (strcmp(commandName, command.name) == 0)
        {
            command.handler(argc, args);

            return;
        }
    }
}

void Terminal::SendPrefix()
{
    std::printf("\n>");
}

void Terminal::SetCommandList(hal::libs::span<const TerminalCommandDescription> commands)
{
    this->_commandList = commands;
}
