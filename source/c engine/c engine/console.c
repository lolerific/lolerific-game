#include "gamedef.h"

char *con_lines[MAX_LINES];
int con_feed = 0;
int curline = 1;
int sepchar = 0;

gboolean con_visible = gfalse;
gboolean con_initialized = gfalse;

void Cmd_ToggleConsole_f()
{
	con_visible = !con_visible;
}

void Con_Init()
{
	Cmd_AddCommand("toggleconsole", Cmd_ToggleConsole_f);
	con_initialized = gtrue;
}