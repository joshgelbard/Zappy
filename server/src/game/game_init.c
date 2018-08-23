#include "server.h"
#include "player_type.h"
#include "tile_type.h"

t_tile		*get_random_tile(void)
{
	int			rx;
	int			ry;

	rx = random() % g_map->dim.x;
	ry = random() % g_map->dim.y;
	return (&g_map->tile[rx][ry]);
}

void		init_teams(int teams, int players)
{
	t_player	*p;
	int			i;
	int			j;

	i = -1;
	j = -1;
	g_map->players = 0;
	while (++i < teams)
	{
		while (++j < players)
		{
			p = new_player(i, j);
			p->tile = get_random_tile();
		}
		j = -1;
		g_map->players_on_team[i] = players;
	}
}

int			game_init(int x, int y, int teams, int players)
{
	int			i;
	int			j;

	i = -1;
	j = -1;
	if ((g_map = malloc(sizeof(t_game_info))) == NULL)
		ERR_OUT("game_init; malloc");
	create_map(x, y);
	g_map->teams = teams;
	player_list_init();
	if ((g_map->empty_avatars = 
				malloc(sizeof(t_plist *) * (teams + 1))) == NULL)
		ERR_OUT("game_init->empty_avatars; malloc");
	bzero(g_map->empty_avatars, sizeof(t_plist *) * (teams + 1));
	if ((g_map->players_on_team = malloc(sizeof(int) * teams)) == NULL)
		ERR_OUT("game_init->players_on_team; malloc");
	init_teams(teams, players);
	return (0);
}
