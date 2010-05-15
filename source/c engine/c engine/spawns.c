#include "gamedef.h"

spawn_t spawns[] = {
	{NULL, NULL},
};

void SP_Spawn(char *name, entity_t *self, char *entityname)
{
	spawn_t *s;

	for(s=spawns;s->name;s++)
	{
		if(!strcmp(s->name, name))
		{
			s->spawn(entityname, self);
			return;
		}
	}
}

void SP_WriteEntities(FILE *f)
{
	entity_t *e;
	spawn_t *s;

	for(s=spawns;s->name;s++)
	{
		for(e=es_entities;e;e=e->next)
		{
			fprintf(f, "%s \"%s\"\n", s->name, e->name);
		}
	}
}