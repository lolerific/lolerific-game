#ifndef ENTITY_H
#define ENTITY_H

#include "gamedef.h"

struct entity_s{
	char *name, *classname;
	char *model;

	void  (*spawn)(struct entity_s *self);
	void  (*activate)(struct entity_s *self);
	void  (*think)(struct entity_s *self);
	void  (*use)(struct entity_s *self, struct entity_s *activator);
	void  (*pain)(struct entity_s *self, int damage);
	void  (*die)(struct entity_s *self, struct entity_s *inflictor, struct entity_s *attacker);

	float thinktime;

	int	health;
	int maxhealth;

	struct entity_s *owner;
	struct entity_s *lastkill;

	vec3_t pos;
	vec3_t desiredpos;
	vec3_t angle;

	struct entity_s *next;
};typedef struct entity_s entity_t;

extern entity_t *es_entities;

void pain(entity_t *self, int damage);
void die(entity_t *self, entity_t *inflictor, entity_t *attacker);

typedef struct{
	entity_t *(*findentity)(char *name);
	void (*linkentity)(entity_t *self);
}entity_system_t;

extern entity_system_t es;

entity_t *_findentity(char *name);
void _linkentity(entity_t *self);

void ES_Init();

#endif //ENTITY_H