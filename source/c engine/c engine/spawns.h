#ifndef SPAWNS_H
#define SPAWNS_H

typedef struct{
	char *name;
	void (*spawn)(char *name, entity_t *self);
}spawn_t;

void SP_Spawn(char *name, entity_t *self, char *entityname);
void SP_WriteEntities(FILE *f);

#endif /*SPAWNS_H*/