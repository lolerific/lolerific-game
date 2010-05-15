#include "gamedef.h"

cmd_t *cmd_cmds;
int cmd_argc;
char *cmd_argv[MAX_ARGS];

gboolean Cmd_CommandExists(char *name)
{
	cmd_t *cmd;
	for(cmd=cmd_cmds; cmd; cmd=cmd->next)
	{
		if(!strcmp(cmd->name, name))
		{
			return gtrue;
		}
	}
	return gfalse;
}

void Cmd_AddCommand(char *name, cmd_func_t function)
{
	cmd_t *cmd;

	if(Cmd_CommandExists(name))
	{
		/*Con_Printf(sa("Command '%s' already exists.\n", name));*/
		return;
	}

	if(Cvar_FindVar(name))
	{
		/*Con_Printf(sa("Command '%s' is a cvar.\n", name));*/
		return;
	}

	cmd = malloc(sizeof(cmd_t));
	cmd->name = name;
	cmd->function = function;
	cmd->next = cmd_cmds;

	cmd_cmds = cmd;
}

char *Cmd_CompleteCommand(char *partial)
{
	cmd_t *cmd;
	int len;

	len = strlen(partial);

	for(cmd = cmd_cmds; cmd; cmd = cmd->next)
	{
		if(!strncmp(cmd->name, partial, len))
		{
			return cmd->name;
		}
	}
	return NULL;
}

int Cmd_Argc()
{
	return cmd_argc;
}

char *Cmd_Argv(int arg)
{
	if(arg > cmd_argc)
		return "";
	return cmd_argv[arg];
}

int Cmd_CheckParam(char *param)
{
	int i;

	if(!param)
	{
		/*Con_Printf("Cmd_CheckParam: Passed string was NULL.\n");*/
		return 0;
	}
	for(i=1; i<Cmd_Argc(); i++)
	{
		if(!strcmp(param, Cmd_Argv(i)))
		{
			return i;
		}
	}

	return 0;
}

void Cmd_Tokenize(char *string)
{
	char *pch;
	int c;

	c = 0;

	pch = strtok(string, " ");
	if(!pch)
	{
		/*Con_Printf("Cmd_Tokenize: Passed string was NULL.\n");*/
		return;
	}

	while(c < MAX_ARGS)
	{
		cmd_argv[c]=pch;
		c++;

		if(!(pch=strtok(NULL," ")))
			return;
	}

	cmd_argc = c;
}

cmd_t *Cmd_FindCommand(char *name)
{
	cmd_t *cmd;
	for(cmd=cmd_cmds; cmd; cmd=cmd->next)
	{
		if(!strcmp(cmd->name, name))
		{
			return cmd;
		}
	}
	return NULL;
}

void Cmd_Echo_f()
{
	int i;
	for(i=1;i<Cmd_Argc();i++)
		continue;
		/*Con_Printf(sa("%s\n",Cmd_Argv(i)))*/
	/*Con_Printf("\n");*/ 
}

void Cmd_WriteVariables_f()
{
	FILE *f;

	if(Cmd_Argc() > 2)
	{
		/*Con_Printf("usage: writevars <filename>\n");*/
		return;
	}

	f = fopen(Cmd_Argv(1), "w");

	if(!f)
	{
		/*Con_Printf(sa("unable to create file '%s'.", Cmd_Argv(1)));*/
		return;
	}

	Cvar_WriteVariables(f);

	fclose(f);
}

void Cmd_Init()
{
	int i;
	cmd_argc = 0;

	for(i=0;i<MAX_ARGS;i++)
		cmd_argv[i]="";

	Cmd_AddCommand("writevars", Cmd_WriteVariables_f);
	Cmd_AddCommand("echo", Cmd_Echo_f);
}