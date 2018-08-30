#include "client_type.h"
#include "player_type.h"
#include "tile_type.h"
#include "command_queue_type.h" 

t_player	*client_controlled_player_on_tile(t_tile *t)
{
	t_player *p;

	for (int i = 0; i < t->num_players; i++)
		if ((p = t->players[i]) && get_client_by_player_id(p->id))
			return (p);
	return (NULL);
}

void		print_player_facing(t_player *p)
{
	printf("%c ", ((char []){ [NORTH] = '^', [EAST] = '>', [SOUTH] = 'v' , [WEST] = '<'}[p->facing]));
}

void			print_tile(t_tile *t)
{
	t_player	*p;

	if (t->num_players == 0)
		printf(". ");
	else if ((p = client_controlled_player_on_tile(t)))
		print_player_facing(p);
	else if (t->num_players <= 9)
		printf("%d ", t->num_players);
	else
		printf("? ");
}

void			animate(void)
{
	static int ticks = 0;

	system("clear");
	printf("[0-9] = num empty bodies, (? if > 9), >^<v = connected client\n\n");
	printf("x = %d, y = %d. tick %d\n", g_map->dim.x, g_map->dim.y, ticks);
	for (int row = 0; row < g_map->dim.y; row++)
	{
		for (int col = 0; col < g_map->dim.x; col++)
		{
			t_tile *t = &g_map->tile[col][row];
			print_tile(t);
		}
		printf("\n");
	}
	++ticks;
}
