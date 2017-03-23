#ifndef HAL_LIBS_TERMINAL_TERMINAL_H_
#define HAL_LIBS_TERMINAL_TERMINAL_H_

#include <cstdint>
#include "hal/libs.h"

/**
 * @defgroup terminal Terminal module
 *
 * @{
 */

/**
 * @brief Type of function used as terminal command handler
 */
using TerminalCommandHandler = void (*)(std::uint8_t argc, char* argv[]);

/**
 * Structure describing single terminal command
 */
struct TerminalCommandDescription {
    /** @brief Name of the command */
    const char* name;
    /** Pointer to handler function */
    TerminalCommandHandler handler;
};

/**
 * @brief Terminal class
 */
class Terminal {
 public:
    /**
     * @brief Sets supported commands list
     * @param[in] commands Commands list
     */
    void SetCommandList(
        hal::libs::span<const TerminalCommandDescription> commands);

    /**
     * @brief Starts terminal
     */
    void Initialize();

    /**
     * @brief Handles incoming command
     * @param[in] buffer Buffer with incoming command
     *
     * After this method ends, @p buffer is no longer usable
     */
    void HandleCommand(char* buffer);

 private:
    /**
     * @brief Sends prefix
     */
    void SendPrefix();

    /**
     * @brief Command list
     */
    hal::libs::span<const TerminalCommandDescription> _commandList;
};

/** @} */

#endif  // HAL_LIBS_TERMINAL_TERMINAL_H_
