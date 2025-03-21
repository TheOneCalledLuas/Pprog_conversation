/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Fernando Mijangos Saul Lopez Romero
 * @version 3
 * @date 29-02-2025
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*Max lenght for a command.*/
#define CMD_LENGHT 30

/**
 * @brief structure with all the possible commands and the key words to triger them.
 */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"l", "Left"}, {"r", "Right"}, {"t", "Take"}, {"d", "Drop"}, {"a", "Attack"}, {"c", "Chat"}};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command
{
    CommandCode code;      /*!< Name of the command. */
    char word[CMD_LENGHT]; /*!< Extra information the player might give.*/
    Status status;         /*!< If the las command had any effect or not.*/
};

Command *command_create()
{
    Command *newCommand = NULL;

    /*Allocation of memory and error management*/
    newCommand = (Command *)malloc(sizeof(Command));
    if (newCommand == NULL)
    {
        return NULL;
    }

    /*Initialization of an empty command.*/
    newCommand->code = NO_CMD;
    newCommand->word[0] = '\0';
    newCommand->status = OK;

    return newCommand;
}

Status command_destroy(Command *command)
{
    /* Error control.*/
    if (!command)
    {
        return ERROR;
    }

    /*Free the memory.*/
    free(command);
    command = NULL;
    return OK;
}

Status command_set_code(Command *command, CommandCode code)
{
    /*Error control.*/
    if (!command)
    {
        return ERROR;
    }

    /*Sets the value.*/
    command->code = code;

    return OK;
}

CommandCode command_get_code(Command *command)
{
    /* Error control.*/
    if (!command)
    {
        return NO_CMD;
    }

    /*Gets the value.*/
    return command->code;
}

char *command_get_word(Command *command)
{
    if (!command)
    {
        return NULL;
    }
    /*Gets the value.*/
    return command->word;
}

Status command_set_word(Command *command, char *word)
{
    /*Error handling.*/
    if (!command || !word)
    {
        return ERROR;
    }

    /*Copies all the letters it can before overflowing to the destionation and the las character is set to \0.*/
    strncpy(command->word, word, CMD_LENGHT);
    command->word[CMD_LENGHT - 1] = '\0';

    return OK;
}

Status command_set_status(Command *command, Status status)
{
    /*Error handling.*/
    if (!command)
    {
        return ERROR;
    }

    /*It copies the value given.*/
    command->status = status;
    return OK;
}

Status command_get_status(Command *command)
{
    return (command ? command->status : ERROR);
}

Status command_get_user_input(Command *command)
{
    char input[CMD_LENGHT] = "", *token = NULL;
    int i = UNKNOWN - NO_CMD + 1;
    CommandCode cmd;

    /* Error control.*/
    if (!command)
    {
        return ERROR;
    }
    command->word[0] = '\0';
    /*1. Gets user input.*/
    if (fgets(input, CMD_LENGHT, stdin))
    {
        token = strtok(input, " \n");
        if (!token)
        {
            /*2.1. If there isnt a word stored in the first token, return unknown command.*/
            return command_set_code(command, UNKNOWN);
        }

        cmd = UNKNOWN;
        /*2.2 Identifies the code of the command entered.*/
        while (cmd == UNKNOWN && i < N_CMD)
        {
            if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))
            {
                cmd = i + NO_CMD;
            }
            else
            {
                i++;
            }
        }
        /*2.3. Return the code that has been identified.*/
        if (!command_set_code(command, cmd))
        {
            return ERROR;
        }

        /*2.4 Assigns the extra word the user might have inputed.*/
        token = strtok(NULL, " \n");
        if (!command_set_word(command, token))
        {
            return ERROR;
        }
        return OK;
    }
    else /*2.5 If it cant read the input from the user, return exit.*/
        return command_set_code(command, EXIT);
}

Status command_print(Command *com, FILE *place)
{
    /*Error handling.*/
    if (!com || !place)
    {
        return ERROR;
    }
    fprintf(place, "Command %s with arguments \"%s\" and exit code ", cmd_to_str[com->code][1], com->word);

    if (com->status == OK)
    {
        fprintf(place, "OK");
    }
    else
    {
        fprintf(place, "ERROR");
    }
    return OK;
}