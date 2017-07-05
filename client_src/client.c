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
#include <sys/mman.h>
#include "../ft_p.h"

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

void ft_put(int sock_id, char **argv, char *line)
{
	int fd;
	char *data;
	struct stat stat;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return;
	if (fstat(fd, &stat) == -1)
		return;
	if ((data = mmap(0, (size_t) stat.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return;
	send(sock_id, line, strlen(line), 0);
	send(sock_id, data, (size_t) stat.st_size, 0);
}

void ft_get(int sock_id, char **argv, char *line)
{
	char *fname;
	int fd;
	char buff[RCVBUFSIZE]; /* Buffer for echo string */
	ssize_t recv_size; /* Size of received message */

	if ((fname = strrchr(argv[1], '/')) == NULL)
		fname = argv[1];
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC | O_EVTONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return;
	send(sock_id, line, strlen(line), 0);
	puts("wating for data");
	recv_size = RCVBUFSIZE;
	while (recv_size == RCVBUFSIZE) {
		if ((recv_size = recv(sock_id, buff, RCVBUFSIZE, 0)) < 0)
			printf("recv() failed");
		else {
			printf("receved %zu\n", recv_size);
			write(fd, buff, (size_t) recv_size);
		}
	}
}

void input_loop(int sock_id)
{
	char *line;
	char **tav;
	int exit_cmd;

	exit_cmd = 1;
	while (exit_cmd && get_next_line(0, &line)) {
		tav = ft_strsplit_fn(line, isspace);
		if (strcmp(tav[0], "put") == 0)
			ft_put(sock_id, tav, line);
		if (strcmp(tav[0], "get") == 0)
			ft_get(sock_id, tav, line);
		else if (send(sock_id, line, strlen(line), 0) != strlen(line)) {
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
	int sock_id;
	struct sockaddr_in server;
	struct hostent *hp;
	char *line;

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