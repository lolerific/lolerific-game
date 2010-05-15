#ifndef CVAR_H
#define CVAR_H

#include "gamedef.h"

typedef enum{
	CVAR_SETGET,
	CVAR_GET,
	CVAR_NONE,
}cvar_mode;

/*shouldn't change these fields outside the Cvar_* functions*/
struct cvar_s{
	char *name;
	char *string;
	gboolean archive;
	gboolean server;
	float value;

	int mode;

	struct cvar_s *next;
}; typedef struct cvar_s cvar_t;

cvar_t *Cvar_FindVar(char *name);
float  Cvar_VariableValue(char *name);
char   *Cvar_VariableString(char *name);
char   *Cvar_CompleteVariable(char *partial);
void   Cvar_Set(char *name, char *value);
void   Cvar_SetValue(char *name, float value);
void   Cvar_RegisterVariable(cvar_t *variable);
/*int  Cvar_Command(){} */ /*checks weather it's a set or get, and displays things accordingly(not implemented yet, no console)*/
void   Cvar_WriteVariables(FILE *f);
void   Cvar_ReadVariables(FILE *f);

extern cvar_t *cvar_vars;

#endif /*CVAR_H*/