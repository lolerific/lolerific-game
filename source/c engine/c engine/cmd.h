#ifndef CMD_H
#define CMD_H

#include "gamedef.h"

#define MAX_ARGS 10

typedef void(*cmd_func_t)();

/*shouldn't change these fields outside the Cmd_* functions!*/
struct cmd_s{
	char *name;
	cmd_func_t function;

	struct cmd_s *next;
}; typedef struct cmd_s cmd_t;

extern cmd_t *cmd_cmds;
extern int cmd_argc;
extern char *cmd_argv[MAX_ARGS];

void Cmd_Init();

void Cmd_AddCommand(char *name, cmd_func_t function);
gboolean Cmd_CommandExists(char *name);

char *Cmd_CompleteCommand(char *partial);

int Cmd_Argc();
char *Cmd_Argv(int arg);

int Cmd_CheckParam(char *param);

void Cmd_Tokenize(char *string);

cmd_t *Cmd_FindCommand(char *name);

#endif /*CMD_H*/