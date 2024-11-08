#include "game_functions.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <windows.h>

void main_function()
{
	progress_bar();
}

void progress_bar()
{
	const uint32_t step = 100;

	puts("the game is loading....");

	for (int32_t i = 0; i <= step; i++)
	{
		printf("\r[");
		for (int32_t j = 0; j < i; j++) 
		{
			printf("#");
		}

		for (int32_t index = step; index > i; index--)
		{
			printf(" ");
		}
		printf("]  (%%%d)", i);

		fflush(stdout);

		Sleep(50);
		
	}
	puts("\n\nThe Game loading is finished! plz select u initial character!");
	puts("\n=================================================================");

}
void create_player(Player* player, const char* P_name, Character char_class) {

	{
		errno_t err;
		err = strncpy_s(player->P_name, sizeof(player->P_name), P_name, _TRUNCATE);
		if (err != 0)
		{
			puts("Error name! plz try again!");
		}

		player->P_name[sizeof(player->P_name) - 1] = '\0';
		player->P_exp = 0;
		player->P_level = 1;
		
		switch (player->P_char_class)
		{
		case Warrior: 
			player->P_health = 150;
			player->P_abilities.strength = 30;
			player->P_abilities.dodge_rate = 5;
			player->P_abilities.crits_rate = 10;
			player->P_abilities.mana = 50;
			player->P_abilities.crits_degree = 2;
			break;
		case Mage:
			player->P_health = 60;
			player->P_abilities.strength = 60;
			player->P_abilities.dodge_rate = 10;
			player->P_abilities.crits_rate = 20;
			player->P_abilities.mana = 100;
			player->P_abilities.crits_degree = 3;
			break;
		case Rogue:
			player->P_health = 80;
			player->P_abilities.strength = 40;
			player->P_abilities.dodge_rate = 50;
			player->P_abilities.crits_rate = 60;
			player->P_abilities.mana = 60;
			player->P_abilities.crits_degree = 5;
			break;
		default:
			break;
		}
	}

}

void generateEnemy(EnemyType enemy_kind, Enemy* enemy)
{
	enemy->E_level = 1;

	switch (enemy_kind)
	{
	case Goblin:
		enemy->E_health = 20;
		enemy->e_ability.strength = 5;
		enemy->e_ability.e_super_one_punch = 2;
		break;
	case Troll:
		enemy->E_health = 10;
		enemy->e_ability.strength = 8;
		enemy->e_ability.e_super_one_punch = 3;
		break;
	case Dragon:
		enemy->E_health = 30;
		enemy->e_ability.strength = 10;
		enemy->e_ability.e_super_one_punch = 5;
	default:
		break;
	}

}

void battle(Player* player, Enemy* enemy, EnemyType t_enemy)
{
	const char* En_name[] = { "Goblin" , "Troll" , "Dragon" };
	
	do
	{
		printf("\nFight!!! the enemy : %s (level %d)  VS  the player : %s (level %d)\n\n", En_name[t_enemy], enemy->E_level, player->P_name, player->P_level);

		puts("Congratulate!!! u Win!");

		player->P_exp += 20 * enemy->E_level;

		if (player->P_exp >= 20 * player->P_level)
		{
			player->P_level++;
		}

	} while (player->P_health > enemy->e_ability.strength);
	
}

