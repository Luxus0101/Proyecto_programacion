
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "game_reader.h"
#include "set.h"
#include "inventory.h"

struct _Inventory
{
    Set *ids;
    long max_obs;
};

Inventory *Inventory_create()
{
    Inventory *I;
    I = (Inventory *)malloc(sizeof(Inventory));
    if (!I)
    {
        return NULL;
    }
    I->max_obs = 0;
    if (!(I->ids = set_create()))
    {
        return NULL;
    }
    return I;
}
STATUS Inventory_destroy(Inventory *I)
{

    if (!(set_destroy(I->ids)))
    {
        return ERROR;
    }
    free(I);
    return OK;
}
STATUS Inventory_add_id(Inventory *I, Id id)
{
    if (I == NULL || id < 0)
    {
        return ERROR;
    }
    if ((set_add(I->ids, id)) == ERROR)
    {
        return ERROR;
    }
    return OK;
}
Id inventory_get_id(Inventory *I, int i)
{
    Id id;
    if ((id = (set_get_id(I->ids, i))) < 0)
        return -1;

    return id;
}

STATUS Inventory_print(Inventory *I)
{
    if (set_print(I->ids) == ERROR)
    {
        return ERROR;
    }
    fprintf(stdout, "\nthe inventory which contains it has %ld objects ", I->max_obs);
    return OK;
}
BOOL Inventory_check_object(Inventory *I, Id id)
{
    if (_set_exist_id(I->ids, id) == TRUE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
long inventory_num_obs(Inventory *I)
{
    return I->max_obs;
}

STATUS Inventory_sub_id(Inventory *I, Id id)
{
    if (id < 0 || I == NULL)
    {
        return ERROR;
    }
    set_del_id(I->ids, id);
    return OK;
}
STATUS inventory_set_max_obs(Inventory *I, long num)
{
    if (I == NULL || num < 0)
    {
        return ERROR;
    }

    I->max_obs = num;
    return OK;
}
long Inventory_get_set_num_ids(Inventory *I)
{
    if (I == NULL)

    {
        return -1;
    }
    return set_get_num_ids(I->ids);
}
