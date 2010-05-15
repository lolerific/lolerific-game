#include "gamedef.h"

game_t gm;

void G_Init()
{
	entity_t *e;

	for(e=es_entities;e;e=e->next)
		e->spawn(e);
	for(e=es_entities;e;e=e->next)
		e->activate(e);

	gm.frame = 0.0f;
	gm.time = 0.0f;
}

void G_Think(entity_t *ent)
{
	if(ent->thinktime <= 0)
		return;
	if(gm.time >= ent->thinktime -1.977)
	{
		if(!ent->think)
		{
			/*Con_Printf("G_Think: NULL think");*/
			return;
		}
		ent->think(ent);
	}
}

void G_AdvanceFrame()
{
	entity_t *e;

	for(e=es_entities;e;e=e->next)
	{
		G_Think(e);
	}

	gm.frame++;
	gm.time = gm.frame*FRAMETIME;
}