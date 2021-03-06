/**
 * @brief It implements the links module
 *
 * @file links.c
 * @author Enrique Ortega Yegros
 * @version 1.0
 * @date 13-04-2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "links.h"

#define MAX_CHAR 100

/**
 * Declaration of the link ADT with its field
 */
struct _Link
{
    Id id;
    char name[MAX_CHAR];
    Id link1;
    Id link2;
    LINK_ST st;
};

Link *link_create()
{
    Link *l = NULL;

    if (!(l = (Link *)malloc(sizeof(Link))))
    {
        return NULL;
    }

    l->id = NO_ID;
    l->link1 = NO_ID;
    l->link2 = NO_ID;
    l->st = Open;
    l->name[0] = '\0';

    return l;
}

void link_destroy(Link *l)
{
    if (l == NULL)
    {
        return;
    }
    free(l);
    l = NULL;
}

STATUS link_setId(Link *l, Id id)
{
    if (l == NULL)
    {
        return ERROR;
    }

    l->id = id;

    return OK;
}

STATUS link_setName(Link *l, const char *name)
{
    if (l == NULL || name == NULL)
    {
        return ERROR;
    }

    if (!(strcpy(l->name, name)))
    {
        return ERROR;
    }

    return OK;
}

STATUS link_setConnections(Link *l, Id id1, Id id2)
{
    if (l == NULL)
    {
        return ERROR;
    }

    l->link1 = id1;
    l->link2 = id2;

    return OK;
}

STATUS link_setStatus(Link *l, LINK_ST st)
{
    if (l == NULL)
    {
        return ERROR;
    }

    l->st = st;

    return OK;
}

Id link_getId(Link *l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->id;
}

char *link_getName(Link *l)
{
    if (l == NULL)
    {
        return NULL;
    }
    char cpy[MAX_CHAR];

    return strcpy(cpy, l->name);
}

Id link_getConnection1(Link *l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->link1;
}

Id link_getConnection2(Link *l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->link2;
}

LINK_ST link_getStatus(Link *l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->st;
}

STATUS link_print(Link *l)
{
    if (l == NULL)
    {
        return ERROR;
    }

    fprintf(stdout, "Link id: %ld\nName:%s\nSpace 1 ID: %ld\nSpace 2 ID: %ld\n", l->id, l->name, l->link1, l->link2);
    if (l->st == Open)
    {
        fprintf(stdout, "Status: OPEN");
    }
    else
    {
        fprintf(stdout, "Status: CLOSED");
    }
    return OK;
}