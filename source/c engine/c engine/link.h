#ifndef LINK_H
#define LINK_H

struct link_s{
	char *name;
	struct link_s *prev, *next;
};typedef struct link_s link_t;

void Link_ClearLink(link_t *link);
void Link_RemoveLink(link_t *link);
void Link_InsertLinkAfter(link_t *link, link_t *after);
void Link_InsertLinkBefore(link_t *link, link_t *before);

#endif //LINK_H