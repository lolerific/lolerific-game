#include "gamedef.h"

entity_system_t es;
entity_t *es_entities;

entity_t *_findentity(char *name)
{
	entity_t *ent2;

	for(ent2 = es_entities; ent2; ent2 = ent2->next)
	{
		if(!strcmp(ent2->name, name))
		{
			return ent2;
		}
	}

	return NULL;
}

void _linkentity(entity_t *self)
{
	entity_t *ent;

	if(!es.findentity(self->name))
	{
		self->next = es_entities;
		es_entities = self;
		return;
	}

	ent = es.findentity(self->name);
	ent = self;
}

void ES_Init()
{
	es.findentity = &_findentity;
	es.linkentity = &_linkentity;
}

void pain(entity_t *self, int damage)
{
	self->health -= damage;
}

void die(entity_t *self, entity_t *inflictor, entity_t *attacker)
{
	self->health = 0;
	inflictor->lastkill = self;
	attacker->lastkill = self;
}