/**
 * @brief Header for module Die. Provides functionality to implement dies.
 *
 * @file die.h
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date  15-03-2021
 * @copyright GNU Public License
 */

#ifndef DIE_H
#define DIE_H

#include "types.h"

#define NO_LAST_STATE 0

typedef struct _Die Die;

/**
 * @brief Creates a die.
 *
 * @param id Id of the new die.
 * @param min Minimal value of the new die.
 * @param max Maximum value of the new die.
 *
 * @return Returns a pointer to a die if it could be created, NULL otherwise.
 **/
Die *die_create(Id id, int min, int max);

/**
 * @brief Destroys the given die and deallocates memory.
 *
 * @param set Pointer to the die to be deallocated.
 *
 * @return Returns OK if the die could be destroyed, ERROR otherwise.
 **/
STATUS die_destroy(Die *die);

/**
 * @brief Assigns a new value to die->last_state.
 *
 * @param die Pointer to the die to be rolled.
 *
 * @return Returns OK if the die could be rolled, ERROR otherwise.
 **/
STATUS die_roll(Die *die);

/**
 * @brief Prints the attributes of the given die.
 *
 * @param f Pointer to the file inside which the contents must be printed.
 * @param die Pointer to the die to be printed.
 *
 * @return Returns OK if the die's contents could be printed, ERROR otherwise.
 **/
STATUS die_print(FILE *f, Die *die);

/**
 * @brief Returns the given die's minimal value.
 *
 * @param die Pointer to the die.
 *
 * @return Returns die->min_val, ERROR if die doesnt exists.
 **/
int die_getMin(Die *die);

/**
 * @brief Assigns a new value to the given die's minimal value.
 *
 * @param die Pointer to the die.
 * @param min New value to be assigned to die->min_val.
 *
 * @return Returns OK if the value could be changed, ERROR if die doesnt exists or min isn't a valid number.
 **/
STATUS die_setMin(Die *die, int min);

/**
 * @brief Returns the given die's maximum value.
 *
 * @param die Pointer to the die.
 *
 * @return Returns die->max_val, ERROR if die doesnt exists.
 **/
int die_getMax(Die *die);

/**
 * @brief Assigns a new value to the given die's maximum value.
 *
 * @param die Pointer to the die.
 * @param max New value to be assigned to die->max_val.
 *
 * @return Returns OK if the value could be changed, ERROR if die doesnt exists or max isn't a valid number.
 **/
STATUS die_setMax(Die *die, int max);

/**
 * @brief Returns the given die's id.
 *
 * @param die Pointer to the die.
 *
 * @return Returns die->id, ERROR if die doesnt exists.
 **/
Id die_getId(Die *die);

/**
 * @brief Assigns a new value to the given die's id.
 *
 * @param die Pointer to the die.
 * @param id New id.
 *
 * @return Returns OK if the value could be changed, ERROR if die doesnt exists or id isn't a valid value.
 **/
STATUS die_setId(Die *die, Id id);

/**
 * @brief Returns the given die's last state.
 *
 * @param die Pointer to the die.
 *
 * @return Returns die->last_state, ERROR if die doesnt exists.
 **/
int die_getLastState(Die *die);


#endif
