/**
 * @brief It defines a screen
 *
 * @file screen.h
 * @author Lucas Piorno Palomo
 * @version 2.0
 * @date 07-02-2021
 * @copyright GNU Public License
 */

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80

typedef struct _Area Area;

void  screen_init();
void  screen_destroy();
void  screen_paint();

Area* screen_area_init(int x, int y, int width, int height);
void  screen_area_destroy(Area* area);
void  screen_area_clear(Area* area);
void  screen_area_reset_cursor(Area* area);
void  screen_area_puts(Area* area, char *str);

#endif
