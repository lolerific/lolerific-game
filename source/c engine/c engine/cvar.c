#include "gamedef.h"

cvar_t *cvar_vars;

cvar_t *Cvar_FindVar(char *name)
{
	cvar_t	*var;
	
	for (var=cvar_vars; var; var=var->next)
		if (!strcmp(name, var->name))
			return var;

	return NULL;
}

float Cvar_VariableValue(char *name)
{
	cvar_t	*var;
	
	var = Cvar_FindVar(name);
	if (!var)
		return 0;
	return atof(var->string);
}

char *Cvar_VariableString(char *name)
{
	cvar_t	*var;
	
	var = Cvar_FindVar(name);
	if (!var)
		return "";
	return var->string;
}

char *Cvar_CompleteVariable(char *partial)
{
	cvar_t *var;
	int len;
	
	len = strlen(partial);
	
	if (!len)
		return NULL;

	for (var=cvar_vars; var; var=var->next)
		if (!strncmp (partial,var->name, len))
			return var->name;

	return NULL;
}

void Cvar_Set(char *name, char *value)
{
	cvar_t	*var;
	int changed;
	
	var = Cvar_FindVar(name);
	if (!var)
	{
		/*Con_Printf(sa("Cvar_Set: cvar '%s' not found.",name));*/
		return;
	}

	changed = strcmp(var->string, value);
	
	free(var->string);
	
	var->string = malloc(strlen(value)+1);
	strcpy(var->string, value);
	var->value = atof(var->string);
	if(var->server && changed)
	{
		/*Con_Printf(sa("'%s' changed to '%s'.", var->name, var->string));*/
		/*should also output to the screen, if the game/server is active*/
	}
}

void Cvar_SetValue (char *var_name, float value)
{
	char val[32];
	
	sprintf(val, "%f",value);
	Cvar_Set(var_name, val);
}

void Cvar_RegisterVariable (cvar_t *variable)
{
	if (Cvar_FindVar (variable->name))
	{
		/*Con_Printf(sa("Cvar_RegisterVariable: cvar '%s' already defined.", variable->name));*/
		return;
	}

	variable->value = atof(variable->string);

	variable->next = cvar_vars;
	cvar_vars = variable;
}

void Cvar_WriteVariables(FILE *f)
{
	cvar_t	*var;
	
	for (var = cvar_vars; var; var = var->next)
	{
		if (var->archive)
		{
			fprintf (f, "%s \"%s\"\n", var->name, var->string);
		}
	}
}