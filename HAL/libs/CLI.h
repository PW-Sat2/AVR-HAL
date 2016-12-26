#ifndef HAL_LIBS_CLI_H_
#define HAL_LIBS_CLI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include "array_view.h"
#include "array.h"

namespace hal {
namespace libs {
namespace CLI {

class Command;

uint8_t nrOfCommands = 0;
libs::array<Command *, 20> commands;

class Command {
 public:
    explicit Command(const char * name) :
            name(name) {
        commands[nrOfCommands++] = this;
    }

    virtual void callback(__attribute__((unused))  const array_view<char *> & parameters) {
    }

    const char * name;

 private:
    bool operator==(const Command &rhs) const {
        if (strcmp(this->name, rhs.name) == 0) {
            return true;
        } else {
            return false;
        }
    }
};

void parse_line(char *line) {
    size_t len = strlen(line);
    uint8_t iter = 0;
    libs::array<char*, 20> params;

    while (line[iter] != ' ' && isalpha(line[iter])) {
        ++iter;
    }
    line[iter] = 0;

    for (int i = 0; i < nrOfCommands; ++i) {
        Command * cmd = commands[i];
        if (strcmp(cmd->name, line) == 0) {
            // found command

            uint8_t param_nr = 0;
            while (iter < len) {
                iter++;
                params[param_nr++] = &line[iter];

                while (line[iter] != ' ' && isalnum(line[iter]))
                    ++iter;
                line[iter] = 0;
            }
            libs::array_view<char *> view(params.data(), param_nr);
            cmd->callback(view);
            return;
        }
    }
    printf("No such command: |%s|!\r\n", line);
}

}  // namespace CLI
}  // namespace libs
}  // namespace hal

#endif  // HAL_LIBS_CLI_H_
