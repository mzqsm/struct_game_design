#include "game_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

void main_function()
{
	int32_t total_points = 0;

	int32_t round = 1;

	progress_bar();

	puts("\nThe Game loading is finished! plz select u initial character!\n");

	Player player;

	char* p_name = (char*)malloc(50 * sizeof(char));

	printf("plz give me u name : ");

	scanf_s("%s", p_name, 50);

	printf("\n");

	int32_t p_class;

	printf("plz give me the num to choose the corresponding character(0->Warrior,1->Mage,2->Rogue) :  ");

	while (true)
	{
		if (scanf_s("%d", &p_class) != 1)
		{
			puts("the undefined character u choose, plz go back and try again!");
			while (getchar() != '\n');
			continue;
		}
		else if (p_class < 0 || p_class > 2)// can't write like 0 <= num <= 2 , it equal to ' (0 <= num) <= 2 '.)
		{
			puts("the undefined character u choose, plz go back and try again!");
		}
		else
		{
			break;
		}
	}
	create_player(&player, p_name, p_class);

	int32_t difficulty;

	char S_diff[3][10] = { "easy", "normal", "hard" };// mentioned! the used of double array!

	printf("plz choose the difficulty u want to challenge : (1->easy, 2->normal, 3->hard)  ");

	while (true)
	{
		if (scanf_s("%d", &difficulty) != 1)
		{
			printf("the unknow difficulty u input, plz check the rule and try again!\n");
			while (getchar() != '\n');
		}
		else if (difficulty < 1 || difficulty > 3)
		{
			printf("the unknow difficulty u input, plz check the rule and try again!\n");
		}
		else
		{
			break;
		}
	}

	printf("OK, let's start your way ! (difficulty : %s)\n", S_diff[difficulty - 1]);

	progress_bar();

	printf("Game Start !\n");

	Enemy* enemy;

	srand(time(NULL));//initial, only need once. can't put in loop.

	enemy->E_level = 1;

	while (true)
	{

		int32_t E_class = 0 + rand() % 3;

		switch (difficulty)
		{
		case 1: generateEnemy(E_class, enemy);
			break;
		case 2: generateEnemy(E_class, enemy);
			break;
		case 3: generateEnemy(E_class, enemy);
			break;
		default:
			break;
		}

		int32_t judge = battle(&player, &enemy, E_class, difficulty, &total_points, &round);

		if (judge == 0)
		{
			break;
		}

	}
	printf("Game Over! total-grades : %d\n", total_points);

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

		Sleep(10);

	}
	puts("\n================================================================================================");

}
void create_player(Player* player, const char* P_name, Character char_class)

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

	switch (char_class)
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
	printf("welcome to this game %s ! here is your basic info :\n", P_name);
	printf("Health : %d\n", player->P_health);
	printf("Mana : %d\n", player->P_abilities.mana);
	printf("now exp : %d\n", player->P_exp);
	printf("Level : %d\n", player->P_level);
	printf("Strength : %d\n", player->P_abilities.strength);
	printf("Dodge-rate : %d%%\n", player->P_abilities.dodge_rate);
	printf("Crits-rate : %d%%\n", player->P_abilities.crits_rate);
	printf("Crits-degree : %d\n", player->P_abilities.crits_degree);
}
void generateEnemy(EnemyType enemy_kind, Enemy* enemy)
{
	char E_race[3][10] = { "Goblin", "Troll", "Dragon" };

	
	// 以后的伏笔，需要注意，以后可能会进行删改！！！

	switch (enemy_kind)
	{
	case Goblin:
		enemy->E_health = 20;
		enemy->e_ability.strength = 5;
		enemy->e_ability.e_super_one_punch = 1;
		break;
	case Troll:
		enemy->E_health = 10;
		enemy->e_ability.strength = 8;
		enemy->e_ability.e_super_one_punch = 2;
		break;
	case Dragon:
		enemy->E_health = 30;
		enemy->e_ability.strength = 10;
		enemy->e_ability.e_super_one_punch = 3;
	default:
		break;
	}

	printf("\nOops! u meet the monster '%s' !\n", E_race[enemy_kind]);
	printf("%s :\n", E_race[enemy_kind]);
	printf("Level : %d\n", enemy->E_level);
	printf("Health : %d\n", enemy->E_health);
	printf("Strength : %d\n", enemy->e_ability.strength);
	printf("Super-one-punch rate : %d%%\n", enemy->e_ability.e_super_one_punch);

}

int32_t battle(Player* player, Enemy* enemy, EnemyType e_class, int32_t difficulty, int32_t* total_points, int32_t* round)
{
	char* En_name[3] = { "Goblin" , "Troll" , "Dragon" };

	printf("\n\nRound : %d\n", *round);

	(*round)++;// *round++ is used to let the 'round' pointer to target the next address, it change the pointer self. (*pointer)++ is used to only change the num of *round .

	printf("Fight!!! the enemy : %s (level %d)  VS  the player : %s (level %d)\n\n", En_name[e_class], enemy->E_level, player->P_name, player->P_level);

	int32_t if_e_Fskill = 1 + rand() % 100;

	if (enemy->e_ability.e_super_one_punch >= if_e_Fskill)
	{
		printf("Ohh.... the monster jumped and use the final attack give u 1000000000 hits!\n");
		return 0;
	}

	int32_t if_dodge = 1 + rand() % 100;

	if (player->P_abilities.dodge_rate >= if_dodge)
	{
		printf("Oohhh! u make a perfect dodge!\n");
		*total_points += 10;
		player->P_health += enemy->e_ability.strength * difficulty * 0.4;
	}

	int32_t if_critic = 1 + rand() % 100;

	if (player->P_abilities.crits_rate >= if_critic)
	{
		printf("Ooh! u make a critical attack!\n");
		*total_points += 10;
		(enemy->E_health) / player->P_abilities.crits_degree;
	}

	if (player->P_abilities.mana >= 20)
	{
		printf("do u want to use the special skill? ( press '1' -> yes! press'0' -> no!)\n");
		int32_t judge;
		scanf_s("%d", &judge);

		int32_t skill = 0;

		if (judge == 1)
		{
			printf("plz select the skill u want to use!\n");
		}

		while (judge)
		{
			if (scanf_s("%d", &skill) != 1)
			{
				printf("u haven't learn this skill! plz check and try again!\n");
				while (getchar() != '\n');
			}
			else if (skill > 3 || skill < 1)
			{
				printf("u haven't learn this skill! plz check and try again!\n");
			}
			else
			{
				break;
			}
		}

		switch (skill)
		{
		case 1:
			printf("Oops, u drink the life potion!\n");
			player->P_health += 20;
			player->P_abilities.mana -= 20;
			break;
		case 2:
			printf("Oops, u drink the strong potion!\n");
			player->P_abilities.strength += 10;
			player->P_abilities.mana -= 20;
			break;
		case 3:
			printf("Oops, u dirnk the super_point potion!\n");
			*total_points += 50;
			player->P_abilities.mana -= 20;
		default:
			break;
		}
	}

	puts("Congratulate!!! u Win!\n");

	player->P_exp += (e_class + 1) * 20 * enemy->E_level;

	printf("u get the '%d' exp from the monster!\n", (e_class + 1) * 20 * enemy->E_level);

	while (player->P_exp >= 20 * player->P_level)
	{
		player->P_level++;
		player->P_exp -= 20 * player->P_level;
		printf("Conguatulate! u update to level '%d' !\n", player->P_level);
		player->P_health += 20;
		player->P_abilities.strength += 5;

		if (player->P_exp < 20 * player->P_level)
		{
			break;
		}
	}

	printf("u need '%d' exp to get the '%d' level !\n", 20 * player->P_level - player->P_exp, (player->P_level) + 1);

	if (player->P_abilities.strength > (enemy->e_ability.strength) * 10)
	{
		enemy->E_health = (enemy->E_health) / 2;
	}
	player->P_health -= enemy->e_ability.strength * difficulty * 0.3 + (enemy->E_health) * 0.1;

	printf("remain health : %d \n", player->P_health);

	printf("remain mana : %d\n", player->P_abilities.mana);

	*total_points += (e_class + 1) * difficulty * 10;

	printf("total points : %d\n", *total_points);

	printf("=========================================================================================\n");

	enemy->E_level++;

	enemy->E_health += 5;

	enemy->e_ability.strength += 3;

	if (player->P_health > enemy->e_ability.strength * difficulty * 0.3 + (enemy->E_health) * 0.1)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


//开发日志（笑） 到了判断如何升级了！ 2024/11/10;

//开发日志2 （xd） 到了给玩家和怪物更新升级后的数值了！ 2024/11/11;
