#ifndef GAME_ABILITIES_H
#define GAME_ABILITIES_H

#include <stdint.h>

typedef struct {		//n选1的时候才用union.
	int32_t strength;
	int32_t mana;
	int32_t crits_rate;
	int32_t dodge_rate;
	int32_t crits_degree;
}ability;

typedef struct {
	int32_t strength;
	int32_t e_super_one_punch;
}E_ability;

#endif