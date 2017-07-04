//
// Created by Robert JONES on 2017/07/04.
//

#include <netinet/in.h>
#include <printf.h>
#include <stdlib.h>
#include <netdb.h>
#include <memory.h>
#include <zconf.h>
#include <libft.h>

int check_port(const char *str)
{
	while (*str) {
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return 1;
}

void connect_to_server(char **av, int sock_id)
{
	struct sockaddr_in server;
	struct hostent *hp;

	server.sin_family = AF_INET;
	printf("av1: %s\n", av[1]);
	hp = gethostbyname(av[1]);
	if (hp == 0) {
		printf("failed to get host from name\n");
		exit(1);
	}
	memcpy(&server.sin_addr, hp->h_addr_list[0], hp->h_length);
	server.sin_port = htons(atoi(av[2]));
	if (connect(sock_id, (const struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("failed to connect\n");
		close(sock_id);
		exit(1);
	}
}

void input_loop(int sock_id)
{
	char	*line;
	int		exit_cmd;

	exit_cmd = 1;
	while( exit_cmd && get_next_line(0,&line))
	{
		if (send(sock_id, line, strlen(line), 0) != strlen(line))
		{
			printf("failed to send data\n");
			close(sock_id);
			free(line);
			exit(1);
		}
		exit_cmd = strcmp(line, "quit");
		free(line);
	}
}

int main(int ac, char **av)
{
	int 				sock_id;
	struct sockaddr_in	server;
	struct hostent 		*hp;
	char				*line;

	if (ac < 3 || check_port(av[2]) == -1) {
		printf("incorrect parameters please use '%s <hostname> <port>'\n\te.g. %s localhost 8080", av[0], av[0]);
		exit(1);
	}
	sock_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock_id < 0) {
		printf("failed to create socket\n");
		exit(1);
	}
	connect_to_server(av, sock_id);

	input_loop(sock_id);

	close(sock_id);
}