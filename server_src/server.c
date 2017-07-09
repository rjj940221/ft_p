//
// Created by rojones on 2017/07/03.
//


#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include "ft_p_server.h"

t_svr_env g_svr_env = (t_svr_env) {-1, -1, -1, NULL};

char *get_client_data(int clntSocket)
{
	char buff[RCVBUFSIZE + 1]; /* Buffer for echo string */
	char *line;
	char *tmp;
	int recv_size; /* Size of received message */

	line = NULL;
	recv_size = RCVBUFSIZE;
	while (recv_size == RCVBUFSIZE)
	{
		if ((recv_size = (int) recv(clntSocket, buff, RCVBUFSIZE, 0)) < 0)
			printf("recv() failed");
		buff[recv_size] = '\0';
		tmp = line;
		line = ft_strjoin(line, buff);
		if (tmp)
			free(tmp);
	}
	printf("Receved: %s\n", line);
	return line;
}

void ft_ls()
{
	DIR *dir;
	struct dirent *dre;
	size_t num_files;

	num_files = 0;
	if (!(dir = opendir(".")))
		printf("\x1b[31mERROR: cannot open dir\n\x1b[0m");
	while (readdir(dir) != NULL)
		num_files++;
	lseek(dirfd(dir), 0, SEEK_SET);
	printf("Num file: %zu\n", num_files);
	errno = 0;
	while ((dre = readdir(dir)) != NULL)
	{
		printf("%s\n", dre->d_name);
	}
	if (errno != 0)
		printf("\x1b[31mERROR: reading dir\n\x1b[0m");
	closedir(dir);
	return;
}

void ft_pwd()
{
	char *pwd;

	pwd = ft_get_pwd();
	printf("PWD: %s\n", pwd);
	if (pwd)
		free(pwd);
}

/*void ft_get(int client, char **argv)
{
	int fd;
	struct stat stat;
	char *data;

	if (ft_checkroot(&argv[1]) == -1)
		return;
	printf("file [%s] in svrroot\n", argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return;
	puts("get opent file");
	if (fstat(fd, &stat) == -1)
		return;
	puts("get got file stat");
	if ((data = mmap(0, (size_t) stat.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return;
	puts("pet got data");
	send(client, data, (size_t) stat.st_size, 0);
}*/

/*void ft_put(int client, char **argv)
{
	char *fname;
	int fd;
	char buff[RCVBUFSIZE]; *//* Buffer for echo string *//*
	ssize_t recv_size; *//* Size of received message *//*

	if ((fname = strrchr(argv[1], '/')) == NULL)
		fname = argv[1];
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return;
	recv_size = RCVBUFSIZE;
	while (recv_size == RCVBUFSIZE) {
		if ((recv_size = recv(client, buff, RCVBUFSIZE, 0)) < 0)
			printf("recv() failed");
		else {
			write(fd, buff, (size_t) recv_size);
		}
	}
}*/


t_bool ft_check_dir(char *dir)
{
	int fd;

	if ((fd = open(dir, O_DIRECTORY)))
	{
		close(fd);
		return (TRUE);
	}
	ft_print_exit("Failed to set server root");
	return (FALSE);
}

void search_builin(t_cmd cmd)
{
	t_builtin_cmd *tmp;

	tmp = g_builtin_cmd;
	while (tmp->cmd)
	{
		if (strcmp(cmd.cmd, tmp->cmd) == 0)
		{
			(*tmp->fnc)(cmd);
			return ;
		}
		tmp++;
	}
	printf("\x1b[mError: Command not recognised '%s'\n\x1b[0m", cmd.cmd);
}

void chiled()
{
	t_cmd cmd;

//	close(g_svr_env.svr_id); todo:uncomment for non blocking
	while (1)
	{
		cmd = ft_get_cmd();
		search_builin(cmd);
	}
}

void perant(pid_t pid)
{
	pid_t perant;
	int stat;

	perant = wait4(pid, &stat, WNOHANG, 0);
	if (perant < 0)
		ft_print_exit("Wait failed");
	close(g_svr_env.cln_cmd);
}

void server_loop()
{
	pid_t pid;

	t_tcp_sock_in client_sock;
	int clientsize;

	clientsize = sizeof(client_sock);
	while (1)
	{
		if ((g_svr_env.cln_cmd = accept(g_svr_env.svr_id, (struct sockaddr *) &client_sock, (socklen_t *) &clientsize)) < 0)
			printf("accept failed\n");
		else
		{
			printf("got client %s\n", inet_ntoa(client_sock.sin_addr));
//			pid = fork();
//			if (pid > -1)
//			{
//				if (pid == 0)
					chiled();
//				else
//					perant(pid);
//			}
		}
	}
}

void ft_svr_init_connection(int port)
{
	g_svr_env.svr_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (g_svr_env.svr_id == -1)
		ft_print_exit("Failed to create socket");
	g_svr_env.sock_in.sin_family = AF_INET;
	g_svr_env.sock_in.sin_port = htons((uint16_t) port);
	g_svr_env.sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(g_svr_env.svr_id, (const struct sockaddr *) &g_svr_env.sock_in, sizeof(t_tcp_sock_in)) == -1)
		ft_print_exit("failed to bind socket\n");
	if (listen(g_svr_env.svr_id, MAX_CLIENTS) == -1)
		ft_print_exit("socket failed to create listener\n");
}

int main(int ac, char **av)
{
	int port;

	if (ac < 2)
	{
		printf("please use %s port_num \n\te.g %s 8080\n", av[0], av[0]);
		return (0);
	}
	if (ac == 2 && check_port(av[1]) == 1)
		port = atoi(av[1]);
	else if (ac == 4 && strcmp(av[1], "-root") && ft_check_dir(av[2]) && check_port(av[3]) == 1)
	{
		g_svr_env.svrroot = strdup(av[2]);
		port = atoi(av[3]);
	}
	if (g_svr_env.svrroot == NULL)
		g_svr_env.svrroot = ft_get_pwd();
	ft_svr_init_connection(port);
	server_loop();
	close(g_svr_env.svr_id);

}

