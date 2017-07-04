//
// Created by rojones on 2017/07/03.
//

//#include <bits/socket_type.h>
//#include <bits/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <zconf.h>
#include <libft.h>
#include "../ft_p_server.h"

int check_port(const char *str)
{
	while (*str) {
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return 1;
}

char *get_client_data(int clntSocket)
{
	char buff[RCVBUFSIZE + 1]; /* Buffer for echo string */
	char *line;
	char *tmp;
	int recv_size; /* Size of received message */

	line = NULL;
	recv_size = RCVBUFSIZE;
	while (recv_size == RCVBUFSIZE) {
		if ((recv_size = (int) recv(clntSocket, buff, RCVBUFSIZE, 0)) < 0) {
			printf("recv() failed");
			//exit(1);
		}
		buff[recv_size] = '\0';
		tmp = line;
		line = ft_strjoin(line, buff);
		if (tmp)
			free(tmp);
	}
	printf("Receved: %s\n", line);
	return line;
}

int get_command(char *line)
{
	int re;
	char *tmp;
	char **tav;

	re = 1;
	tmp = ft_strtrim(line);
	tav= ft_strsplit_fn(line, isspace);
	if (strcmp(tav[0], "quite") == 0)
		re = 0;
	if (line)
		free(line);
	if (tmp)
		free(tmp);
	return re;
}

void chiled(int sockid, int client)
{
	int exit_loop;

	exit_loop = 1;
	close(sockid);
	while (exit_loop)
		exit_loop = get_command(get_client_data(client));
	close(client);
	exit(0);
}

void perant(int client, pid_t pid)
{
	pid_t perant;
	int stat;

	perant = wait4(pid, &stat, WNOHANG, 0);
	if (perant < 0) {
		printf("wait failed\n");
		exit(1);
	}
	close(client);
}

void server_loop(int sockid)
{
	pid_t pid;

	t_tcp_sock_in client_sock;
	int client;
	int clientsize;



	clientsize = sizeof(client_sock);
	while (1) {
		if ((client = accept(sockid, (struct sockaddr *) &client_sock, (socklen_t *) &clientsize)) < 0) {
			printf("accept failed\n");
			//exit(1);
		} else {
			printf("got client %s\n", inet_ntoa(client_sock.sin_addr));
			pid = fork();
			if (pid > -1) {
				if (pid == 0)
					chiled(sockid, client);
				else {
					perant(client, pid);
				}
			}
		}
	}
}

void printenv(char **env)
{
	while (*env)
		printf("%s\n", *(env++));
}

int main(int ac, char **av, char **env)
{
	printenv(env);

	int sockid;
	t_tcp_sock_in sock_in;

	if (ac < 2 || check_port(av[1]) == -1) {
		printf("please use %s port_num \n\te.g %s 8080\n", av[0], av[0]);
		return (0);
	}

	sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockid == -1) {
		printf("Failed to create socket");
		return 0;
	}
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons((uint16_t) atoi(av[1]));
	sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockid, (const struct sockaddr *) &sock_in, sizeof(sock_in)) == -1) {
		printf("failed to bind socket\n");
		close(sockid);
		exit(1);
	}
	if (listen(sockid, MAX_CLIENTS) == -1) {
		printf("socket failed to create listener\n");
		close(sockid);
		exit(1);
	}
	server_loop(sockid);
	close(sockid);
}

