#include "server.h"

int	main(int argc, char **argv)
{
	t_command_list	*cmds;
	int				winning_team_id;
	int				fd;
	t_client		**user_clients;

	parse_command_line_options(argc, argv);
	listen_for_connections(g_opts.server_port);
	while (1)
	{
		user_clients = get_clients();
		while ((fd = get_socket_with_available_data()) != -1)
			handle_waiting_connection_data(fd);
		if (have_we_ticked())
		{
			remove_dead_players();
			cmds = dequeue_commands(user_clients);
			execute_command_list(cmds);
			if (is_game_over(&winning_team_id))
				handle_game_over(winning_team_id);
			send_results_to_users(cmds);
			free_cmdlist(cmds);
			decrement_user_command_timers(user_clients);
		}
	}
	return (0);
}
