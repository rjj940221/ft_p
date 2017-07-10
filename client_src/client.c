//
// Created by Robert JONES on 2017/07/04.
//



#include "ft_p_client.h"

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
	printf("ip to connect to: %s\n", inet_ntoa(server.sin_addr));
	server.sin_port = htons((uint16_t) atoi(av[2]));
	printf("sizeof struct: %zu\n", sizeof(server));
	if (connect(g_clt_env.svr_cmd_sock, (const struct sockaddr *) &server, sizeof(server)) < 0)
		ft_print_exit("failed to create command connection");
	puts(ft_get_addr_str(g_clt_env.svr_cmd_sock));
}

void search_builin(char *line)
{
	char **tav;
	t_builtin_cmd *tmp;

	tav = ft_strsplit_fn(line, isspace);
	tmp = g_builtin_cmd;
	while(tmp->cmd)
	{
		if (strcmp(tav[0], tmp->cmd) == 0)
		{
			(*tmp->fnc)(tav);
			return ;
		}
		tmp++;
	}
	printf("\x1b[mError: Command not recognised'%s'\n\x1b[0m",tav[0]);
}


void ft_wait_responce()
{
	t_cmd_rsp	rsp;

	rsp = ft_get_cmd_responce();
	ft_process_rsp(rsp);
}

void ft_process_rsp(t_cmd_rsp	rsp)
{
	/*if (rsp.code >= 100 && rsp.code<200)
		ft_get_cmd_responce();*/
	if (rsp.code >= 200 && rsp.code < 300)
		printf("SUCCESS(%d): %s\n", rsp.code, rsp.msg);
	if (rsp.code >= 300 && rsp.code < 400)
		printf("PENDING(%d): %s\n", rsp.code, rsp.msg);
	if (rsp.code >= 400 && rsp.code < 600)
		printf("\x1b[31mERROR(%d):\x1b[0m %s\n", rsp.code, rsp.msg);
	g_clt_env.wait_rsp = FALSE;
}

void input_loop()
{
	char *line;

	while (1)
	{
		if (g_clt_env.wait_rsp)
			ft_wait_responce();
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