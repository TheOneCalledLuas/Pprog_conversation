/**
 * @brief It defines the command interpreter interface.
 *
 * @file command.h
 * @author Fernando Mijangos, Saul Lopez Romero, Raquel Anguita Martínez de Velasco
 * @version 1
 * @date 29-02-2025
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>

#include "types.h"
/**
 * Ways of refering to the same command.*/
#define N_CMDT 2
/**
 * Number of commands.*/
#define N_CMD 11

/**
 * @brief Ways of calling a command (extended or short way.)
 * Example: You can call the exit command with e or with exit.
 */
typedef enum
{
    CMDS,       /*!< Command to be accessed.*/
    CMDL        /*!< Short or long command name.*/
} CommandType;

/**
 * @brief Code assigned to each command.
 */
typedef enum
{
    NO_CMD = -1,    /*!< No Coomand code.*/
    UNKNOWN,        /*!< Unknown command.*/
    EXIT,           /*!< Exit command.*/
    MOVE,           /*!< Move command.*/
    TAKE,           /*!< Take command.*/
    DROP,           /*!< Drop command.*/
    ATTACK,         /*!< Attack command.*/
    CHAT,           /*!< Chat command.*/
    INSPECT,        /*!< Inspect command.*/
    RECRUIT,        /*!< Recruit command.*/
    ABANDON         /*!< Abandon command.*/
} CommandCode;
/**
 * @brief Command
 * Command structure.
 */
typedef struct _Command Command;

/**
 * @brief It creates a new command, allocating memory and initializing its members.
 * @author Saúl lopez
 *
 * @return Pointer to a new command, initialized.
 */
Command *command_create();

/**
 * @brief It destroys an existing command, freeing the allocated memory.
 * @author Saúl lopez
 *
 * @param command Pointer to the space that needs to be destroyed.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_destroy(Command *command);

/**
 * @brief It sets the code that will be stored in command.
 * @author Saúl lopez
 *
 * @param command Pointer to the command that will recive the code.
 * @param code  Code that will be stored.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_set_code(Command *command, CommandCode code);

/**
 * @brief It gets the code that is stored in a command.
 * @author Saúl lopez
 *
 * @param command Pointer to the command.
 * @return Code stored in the command.
 */
CommandCode command_get_code(Command *command);

/**
 * @brief It sets the status of the command.
 * @author Fernando Mijangos
 * 
 * @param command Pointer to the command.
 * @param status New status.
 * @return OK if everything went well, ERROR otherwise.
 */
Status command_set_status(Command *command, Status status);

/**
 * @brief It gets the status stored in a command.
 * @author Fernando Mijangos
 *
 * @param command Pointer to the command.
 * @return Status of the command.
 */
Status command_get_status(Command *command);

/**
 * @brief Returns the word stored in the command.
 * @author Fernando Mijangos
 * 
 * @param command Pointer to the command.
 * @return String the the word contains or NULL if something went wrong.
 */
char *command_get_word(Command *command);

/**
 * @brief Sets the word of the command the the defined one.
 * @author Fernando Mijangos
 * 
 * @param command Pointer to the command structure.
 * @param word string that will be copied.
 * @return OK, if everything went well, ERROR if it didnt't.
 */
Status command_set_word(Command *command, char *word);

/**
 * @brief Reads an input from the user, and assigns a code to command depending on the input.
 * @author Fernando Mijangos
 *
 * @param command Pointer to the command where you will store the information.
 * @return OK if everything goes well or ERROR if there was some mistake.
 */
Status command_get_user_input(Command *command);

/**
 * @brief Prints the command information.
 * @author Raquel Anguita Martínez de Velasco
 *
 * @param com Pointer to the command where you will store the information.
 * @param place place to write the outcome (stdout or file intended).
 * @return OK if everything goes well or ERROR if there was some mistake. 
 */
Status command_print(Command *com, FILE *place);

#endif
