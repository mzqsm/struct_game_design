#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H
	
#include "game_structs.h"
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>



void main_function();

void create_player(Player* player, const char* name, Character char_class);

void generateEnemy(EnemyType enemy_kind);

void battle(Player* player, Enemy* enemy);

void print_player_info(const Player* player);

void print_enemy_info(const Enemy* enemy);

void progress_bar();

#endif 

