#include "server.h"
#include "player_type.h"
#include "g_player_list.h"

t_player	**g_player_list = NULL;
int			g_list_size = START_SIZE;

int				grow_list(void)
{
	g_player_list = realloc(g_player_list, sizeof(t_player *) * (g_list_size * 2));
	if (!g_player_list)
		ERR_OUT("grow list; realloc");
	bzero(g_player_list + g_list_size, g_list_size);
	g_list_size *= 2;
	return (0);
}

void			player_list_init(void)
{
	if ((g_player_list = calloc(START_SIZE, sizeof(t_player *))) == NULL)
		ERR_OUT("player list; malloc");
}

int				add_player_to_list(t_player *t)
{
	if (t->id >= g_list_size)
		grow_list();
	g_player_list[t->id] = t;
	return (0);
}

t_player		*get_player(int pid)
{
	if (pid >= g_list_size)
		return (NULL);
	return (g_player_list[pid]);
}

int				get_player_list_size(void)
{
	return (g_list_size);
}