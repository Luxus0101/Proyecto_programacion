#ifndef DICE_H
#define DICE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"


typedef struct _Dice Dice;
/**
 * @brief creates a dice like structure
 * 
 * @param id 
 * @return Dice* 
 */
Dice *dice_create(Id id);
 /**
 * @brief frees a dice type structure
 * 
 * @param dice 
 * @return STATUS 
 */
STATUS dice_destroy(Dice *dice);
/**
 * @brief obtains a random number in a defined range
 * 
 * @param dice 
 * @return STATUS 
 */
STATUS dice_roll(Dice *dice);
/**
 * @brief prints on screen the values found inside of a dice structure
 * 
 * @param dice 
 * @return STATUS 
 */
STATUS dice_print(Dice *dice);
/**
 * @brief checks for the last obtained dice roll
 * 
 * @param dice 
 * @return int 
 */
int dice_last_roll(Dice *dice);

#endif
