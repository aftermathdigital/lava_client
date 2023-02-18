#ifndef LAVALIB_H
#define LAVALIB_H

#include <stdint.h>

int get_handle();
void close_handle(int);
long new_crucible(int, uint16_t, uint8_t, uint8_t);
long add_pebble(int, uint16_t, uint16_t, uint16_t, uint16_t);
long remove_pebble(int, uint16_t, uint16_t);
long assess_value(int, uint16_t);
long incinerate(int, uint16_t);

#endif