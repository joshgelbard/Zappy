#include "test.h"
#include "player_type.h"
#include "tile_type.h"

#define ASSERT_OK(x) assert(!strcmp(x, "ok\n"))
#define ASSERT_KO(x) assert(!strcmp(x, "ko\n"))

void	test_user_command_advance(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];

	assert(!strcmp(advance(p1->id, NULL), "ok\n"));
	assert(is_player_on_tile(p1, &g_map->tile[1][1]) == p1);
	assert(!strcmp(advance(p1->id, NULL), "ok\n"));
	assert(is_player_on_tile(p1, &g_map->tile[1][0]) == p1);
	printf("%s: ok\n", __func__);
}

void	test_user_commands_left_and_right(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];

	left(p1->id, NULL);
	assert(p1->facing == EAST);
	left(p1->id, NULL);
	assert(p1->facing == NORTH);
	left(p1->id, NULL);
	assert(p1->facing == WEST);
	left(p1->id, NULL);
	assert(p1->facing == SOUTH);

	right(p1->id, NULL);
	assert(p1->facing == WEST);
	right(p1->id, NULL);
	assert(p1->facing == NORTH);
	right(p1->id, NULL);
	assert(p1->facing == EAST);
	right(p1->id, NULL);
	assert(p1->facing == SOUTH);
	printf("%s: ok\n", __func__);
}

void	test_user_commands_put_and_take(void)
{
	init_user_commands_test_gamestate();
	t_player *p1 = g_map->tile[1][0].players[0];
	t_player *p2 = g_map->tile[2][0].players[0];

	ASSERT_OK(take(p1->id, stone_names[1]));
	assert(p1->stones[1] == 1);
	assert(p1->tile->stones[1] == 0);

	ASSERT_KO(take(p1->id, stone_names[1]));
	assert(p1->stones[1] == 1);

	ASSERT_KO(take(p1->id, stone_names[2]));
	assert(p1->stones[2] == 0);

	ASSERT_OK(put(p1->id, stone_names[1]));
	assert(p1->stones[1] == 0);
	assert(p1->tile->stones[1] == 1);

	ASSERT_OK(put(p2->id, stone_names[3]));
	ASSERT_OK(put(p2->id, stone_names[3]));
	ASSERT_KO(put(p2->id, stone_names[3]));
	assert(p2->tile->stones[3] == 2);

	printf("%s: ok\n", __func__);
}

void	test_user_command_connect_nbr(void)
{
}

void	test_user_commands(void)
{
	test_user_command_advance();
	test_user_commands_left_and_right();
	test_user_commands_put_and_take();
	test_user_command_connect_nbr();
}
