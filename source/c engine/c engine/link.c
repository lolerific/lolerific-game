#include "gamedef.h"

void Link_ClearLink(link_t *link)
{
	link->prev = link->next = link;
}

void Link_RemoveLink(link_t *link)
{
	link->prev->next = link->next;
	link->next->prev = link->prev;
}

void Link_InsertLinkAfter (link_t *link, link_t *after)
{
	link->next = after->next;
	link->prev = after;
	link->prev->next = link;
	link->next->prev = link;
}

void Link_InsertLinkBefore(link_t *link, link_t *before)
{
	link->next = before;
	link->prev = before->prev;
	link->prev->next = link;
	link->next->prev = link;
}