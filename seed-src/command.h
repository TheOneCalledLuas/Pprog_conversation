/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Profesores PPROG && Fernando Mijangos
 * @version 1
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"
/*Ways of refering to the same command.*/
#define N_CMDT 2
/*Number of commands.*/
#define N_CMD 7

/**
 * @brief Ways of calling a command (extended or short way.)
 * Example: You can call the exit command with e or with exit.
 */
typedef enum
{
    CMDS,
    CMDL
} CommandType;

/**
 * @brief Code assigned to each command.
 */
typedef enum
{
    NO_CMD = -1,
    UNKNOWN,
    EXIT,
    NEXT,
    BACK,
    TAKE,
    DROP
} CommandCode;
/**
 * @brief Command
 * command structure.
 */
typedef struct _Command Command;

/**
 * @brief It creates a new command, allocating memory and initializing its members.
 * @author Profesores PPROG
 *
 * @return Pointer to a new command, initialized.
 */
Command *command_create();

/**
 * @brief It destroys an existing command, freeing the allocated memory.
 * @author Profesores PPROG
 *
 * @param command Pointer to the space that needs to be destroyed.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_destroy(Command *command);

/**
 * @brief It sets the code that will be stored in command.
 * @author Profesores PPROG
 *
 * @param command Pointer to the command that will recive the code.
 * @param code  Code that will be stored.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief It gets the code that is stored in a command.
 * @author Profesores PPROG
 *
 * @param command Pointer to the command.
 * @return Code stored in the command.
 */
CommandCode command_get_code(Command *command);

/**
 * @brief Reads an input from the user, and assigns a code to command depending on the input.
 * @author Profesores PPROG
 *
 * @param command Pointer to the command.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_get_user_input(Command *command);

#endif
