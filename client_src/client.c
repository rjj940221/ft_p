//
// Created by Robert JONES on 2017/07/04.
//


#include "../ft_p_client.h"

t_clt_env g_clt_env = (t_clt_env) {FALSE, -1};

void connect_to_server(char **av)
{
	struct sockaddr_in server;
	struct hostent *hp;

	server.sin_family = AF_INET;
	printf("Host: %s\n", av[1]);
	hp = gethostbyname(av[1]);
	if (hp == 0)
	{
		printf("failed to get host from name\n");
		exit(1);
	}
	memcpy(&server.sin_addr, hp->h_addr_list[0], hp->h_length);
	server.sin_port = htons(atoi(av[2]));
	if (connect(g_clt_env.svr_cmd_sock, (const struct sockaddr *) &server, sizeof(server)) < 0)
		ft_print_exit("failed to create command connection");
}

void search_builin(char *line)
{
	char **tav;
	t_builtin_cmd *tmp;

	tav = ft_strsplit_fn(line, isspace);
	tmp = g_builtin_cmd;
	while(tmp)
	{
		if (strcmp(tav[0], tmp->cmd) == 0)
			(*tmp->fun)(tav);
		tmp++;
	}
	printf("\x1b[mError: Command not recognised'%s'\n\x1b[0m",tav[0]);
}


void input_loop()
{
	char *line;

	while (1)
	{
		get_next_line(0, &line);
		search_builin(line);
		free(line);
	}
}

int main(int ac, char **av)
{
	struct sockaddr_in server;
	struct hostent *hp;
	char *line;

	if (ac < 3 || check_port(av[2]) == -1)
	{
		printf("incorrect parameters please use '%s <hostname> <port>'\n\te.g. %s localhost 8080", av[0], av[0]);
		exit(1);
	}
	if ((g_clt_env.svr_cmd_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ft_print_exit("failed to create socket");
	connect_to_server(av);
	input_loop();
}