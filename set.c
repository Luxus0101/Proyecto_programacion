#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "set.h"

struct _Set
{
    Id vectors[ID_SIZE];
    long num_ids;
};

Set *set_create()
{

    Set *s = NULL;

    if (!(s = (Set *)malloc(sizeof(Set))))
    {
        return NULL;
    }
    for (int i = 0; i < ID_SIZE; i++)
    {
        s->vectors[i] = 0;
    }
    s->num_ids = 0;

    return s;
}
STATUS set_destroy(Set *s)
{

    if (s == NULL)
    {
        return ERROR;
    }

    free(s);

    s = NULL;

    return OK;
}
STATUS set_add(Set *s, Id id)
{
    if (s == NULL || id < 0 || id > ID_SIZE)
    {
        return ERROR;
    }

    s->vectors[s->num_ids] = id;

    s->num_ids++;

    return OK;
}
STATUS set_del_id(Set *s, Id id)
{
    if (s == NULL || id < 0 || id > ID_SIZE)
    {
        return ERROR;
    }
    int i;

    for (i = 0; i < s->num_ids && i < ID_SIZE; i++)
    {
        if (id == s->vectors[i])
            break;
    }

    if (i == (s->num_ids - 1))
    {
        s->vectors[i] = NO_ID;
        s->num_ids--;
        return OK;
    }

    else
    {
        s->num_ids--;

        s->vectors[i] = s->vectors[s->num_ids];

        s->vectors[s->num_ids] = NO_ID;
    }
    return OK;
}
STATUS set_print(Set *s)
{
    if (s == NULL)
    {
        return ERROR;
    }

    fprintf(stdout, "set includes: %ld, from which we obtain the following vectors: ", s->num_ids);

    for (int i = 0; i < s->num_ids && i < ID_SIZE; i++)
    {
        fprintf(stdout, "%ld ", s->vectors[i]);
    }

    return OK;
}
BOOL _set_exist_id(Set *s, Id id)
{
    if (s == NULL || id < 0)
    {
        return FALSE;
    }
    int i;
    for (i = 0; i < ID_SIZE && i < s->num_ids; i++)
    {
        if (id == s->vectors[i])
            return TRUE;
    }

    return FALSE;
}

long set_get_id(Set *s, int i)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->vectors[i];
}
long set_get_num_ids(Set *s)
{
    if (s == NULL)
    {
        return -1;
    }
    return s->num_ids;
}

long *set_getVectors(Set *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    long *nv;
    if (!(nv = (long *)calloc(s->num_ids, sizeof(long))))
    {
        return NULL;
    }
    for (int i = 0; i < s->num_ids; i++)
    {
        nv[i]=s->vectors[i];
    }

    return nv;
}
