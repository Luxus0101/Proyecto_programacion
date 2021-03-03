/**
 * @brief It defines common types
 *
 * @file types.h
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date 21-02-2021
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;

typedef enum {
  FALSE, TRUE
} BOOL;

typedef enum {
  ERROR, OK
} STATUS;

typedef enum {
  N, S, E, W
} DIRECTION;

#endif
