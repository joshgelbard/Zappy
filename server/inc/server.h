
#ifndef SERVER_H
# define SERVER_H
# include <arpa/inet.h>
# include <assert.h>
# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <unistd.h>

# define ERR_OUT(msg)		({ perror(msg); exit(-1); })
# define CMD_COUNTDOWN(plr)	(plr->cmd_list->delay_cycles)
# define CMD_READY(plr)		(CMD_COUNTDOWN(plr) == 0)
# define DO_CMD_FUNC(cmd)	(cmd->do_cmd(cmd->player_id, cmd->args))
# define NEXT_CMD(cmd)		(cmd = cmd->next)

# define LINEMATE 0
# define DERAUMERE 1
# define SIBUR 2
# define MENDIANE 3
# define PHIRAS 4
# define THYSTAME 5

# define DEFAULT_PARRAY 8

# define DEFAULT_FOOD 0
# define DEFAULT_ENERGY 1260
# define DEFAULT_LEVEL 1
# define EGG_TIMER 300
# define ENERGY_PER_FOOD 126

enum					e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST
};

typedef struct			s_tile
{
	struct s_player		**players;
	int					parray_size;
	int					num_players;
	int					stones[6];
	int					food;
	int					x;
	int					y;
}						t_tile;

typedef struct			s_player
{
	struct s_tile		*tile;
	int					facing;
	int					stones[6];
	int					food;
	int					energy;
	int					level;
	int					id;
	int					team_id;
	int					team_pid;
	int					egg;
}						t_player;

typedef struct			s_plist
{
	t_player			*p;
	struct s_plist		*next;
}						t_plist;

typedef struct			s_game_info
{
	t_tile				**tile;
	t_vec				dim;
	int					teams;
	int					*players_on_team;
	t_plist				**empty_avatars;
}						t_game_info;

typedef char			*(*t_cmd_func)(int, void *);

typedef struct			s_cmd
{
	struct s_cmd		*next;
	int					player_id;		//Can we do this better?
	t_cmd_func			do_cmd;
	void				*args;
	int					timestamp;
	int					delay_cycles;
}						t_cmd;

typedef struct			s_cmd_queue
{
	struct s_cmd_queue	*next_plr;
	struct s_cmd		*cmd_list;
	int					player_id;
	int					cmd_count;
}						t_cmd_queue;

/*
** Global Variables:
*/

t_game_info					*g_map;

/*
** server.c
*/

int						get_server_socket(int port);
int						accept_and_poll_clients(int server);

/*
** Player api:
*/

t_player				*get_player(int pid);

/*
**	player_actions.c:
*/

void					turn_left(int pid);
void					turn_right(int pid);

int						attempt_to_take(int pid, char *obj);
int						attempt_to_put(int pid, char *obj);


/*
** Game Engine Functions:
*/

int						create_map(int, int);
int						place_stone(int type, t_tile *t);
int						player_place_stone(int type, t_tile *t, t_player *player);
int						remove_stone(int type, t_tile *t);
int						pickup_stone(int type, t_tile *t, t_player *player);

int						place_random_stones(int type, int pool);
int						place_random_food(int pool);
int						player_place_food(t_tile *tile, t_player *player);
int						pickup_food(t_tile *t, t_player *player);
int						move_player(int pid, int dir);

t_tile					*get_adj_tile(t_tile *home, int dir);
t_tile					*get_tile_NS(t_tile *home, int v);
t_tile					*get_tile_EW(t_tile *home, int v);

t_player				*new_player(int egg, int team_id, int team_pid);
int						get_new_player_id(void);
void					cleanup_player_list(void);
t_player				*get_player(int pid);
int						add_player_to_list(t_player *t);
int						grow_list(void);
int						add_player_to_team_waitlist(t_player *p);
t_player				*remove_player_from_waitlist(int team);

/*
** User commands:
*/

char					*advance(int player_id, void *arg);
char 					*turn(int player_id, void *arg);
char 					*see(int player_id, void *arg);
char 					*inventory(int player_id, void *arg);
char 					*take(int player_id, void *arg);
char 					*put(int player_id, void *arg);
char 					*kick(int player_id, void *arg);
char 					*broadcast(int player_id, void *arg);
char 					*incantation(int player_id, void *arg);
char 					*fork_player(int player_id, void *arg);
char 					*connect_nbr(int player_id, void *arg);

/*
** Scheduler commands
*/

typedef char			*(*t_cmd_func)(int, void *);

int						schd_step_cycle(t_cmd **lit_cmds);
int						schd_add_plr(int player_id);
int						schd_kill_plr(int player_id);
int						schd_add_cmd(int player_id, t_cmd_func cmd,
										void *args, int delay_cycles);

/*
** Executioner commands
*/

int						exec_utioner(t_cmd *cmd_exec_list);
void					exec_free_cmds(t_cmd *list);

#endif
