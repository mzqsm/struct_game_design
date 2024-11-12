#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H
	
#include "game_structs.h"
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>



void main_function();

void create_player(Player* player, const char* name, Character char_class);

void generateEnemy(EnemyType enemy_kind, Enemy* enemy, int32_t* new_level);

int32_t battle(Player* player, Enemy* enemy, EnemyType e_class, int32_t difficulty, int32_t* total_points, int32_t* round);

void progress_bar();

#endif 

