#include "dice.h"

struct _Dice
{
    Id id;
    int maximum;
    int minimum;
    int last_roll;
};

STATUS dice_destroy(Dice *dice)
{
    if (dice == NULL)
    {
        return ERROR;
    }
    free(dice);
    dice = NULL;
    return OK;
}

STATUS dice_print(Dice *dice)
{
    if (dice == NULL)
    {
        return ERROR;
    }
    fprintf(stdout, "Id: %ld", dice->id);
    fprintf(stdout, "Max: %d", dice->maximum);
    fprintf(stdout, "Min: %d", dice->minimum);
    fprintf(stdout, "Last roll: %d", dice->last_roll);
    return OK;
}

STATUS dice_roll(Dice *dice)
{
    if (dice == NULL)
    {
        return ERROR;
    }

    int result = 0, low_num = 0, hi_num = 0;

    if (dice->minimum < dice->maximum)
    {
        low_num = dice->minimum;
        hi_num = dice->maximum + 1;
    }
    else
    {
        low_num = dice->maximum + 1;
        hi_num = dice->minimum;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;;
    dice->last_roll=result;
    return OK;
}
Dice *dice_create(Id id)
{
    if (id<0)
    {
        return NULL;
    }
    Dice *d;

    d=(Dice *)malloc(sizeof(Dice));
    if (d == NULL)
    {
    return NULL;
    }
    d->id = id;
    d->maximum=6;
    d->minimum=1;
    d->last_roll = 0;
    return d;
}

int dice_last_roll (Dice *dice)
{
    if (dice==NULL)
    {
        return -1;
    }

    return dice->last_roll;
}
