#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "character_create.h"
#include "game_abilities.h"

typedef struct {
	char P_name[50];
	Character P_char_class;
	ability P_abilities;
	int32_t P_level;
	int32_t P_health;
	int32_t P_exp;
}Player;

typedef struct {
	int32_t E_level;
	E_ability e_ability;
	int32_t E_health;
}Enemy;

typedef struct {
	char name[50];
	itemtype type;
	int32_t power;
	int32_t exp_bottle;
	int32_t recover_strength;
	int32_t recover_mana;
}tool;


#endif
