//
// Created by rojones on 2017/07/03.
//

//#include <bits/socket_type.h>
//#include <bits/socket.h>

#include "../ft_p_server.h"

t_svr_env g_svr_env;

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

char *get_pwd()
{
	char *buff;

	buff = NULL;
	buff = getcwd(buff, MAXPATHLEN);
	return (buff);
}

void ft_abspath(char **str)
{
	char *tmp;
	char *pwd;

	pwd = get_pwd();
	if (*str) {
		if ((*str)[0] == '~') {
			tmp = *str;
			*str = ft_strjoin("/nfs/zfs-student-6/users/rojones", &(*str)[1]);
			free(tmp);
		} else if ((*str)[0] != '/') {
			tmp = pwd;
			pwd = ft_strjoin(pwd, "/");
			free(tmp);
			tmp = *str;
			*str = ft_strjoin(pwd, *str);
			free(tmp);
		}
	}
	free(pwd);
}

int ft_checkroot(char **str)
{
	char	*pwd;
	int		re;

	pwd = get_pwd();
	re = -1;
	printf("checking path for ..[%s]\n", *str);
	if (strncmp(*str, "..", 2) == 0 && (strlen(pwd) == strlen(g_svr_env.svrroot))) {
		printf("\x1B[31mERROR: not in server root\n\x1b[0m");
		free(pwd);
		return (-1);
	}
	puts("make call to abspath");
	ft_abspath(str);
	puts("past abspath");
	printf("checking path in root[%s]\n", *str);
	if (strncmp(*str, g_svr_env.svrroot, strlen(g_svr_env.svrroot)) == 0)
		re = 1;
	else
		printf("\x1B[31mERROR: not in server root\n\x1b[0m");
	free(pwd);
	return (re);
}

void ft_ls()
{
	DIR *dir;
	struct dirent *dre;
	size_t num_files;

	num_files = 0;
	if (!(dir = opendir(".")))
		printf("\x1b[31mERROR: cannot open dir\n\x1b[0m");
	printf("dir len: %d\n", dir->__dd_len);
	while (readdir(dir) != NULL)
		num_files++;
	lseek(dir->__dd_fd, 0, SEEK_SET);
	printf("Num file: %zu\n", num_files);
	errno = 0;
	while ((dre = readdir(dir)) != NULL) {
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

	pwd = get_pwd();
	printf("PWD: %s\n", pwd);
	if (pwd)
		free(pwd);
}

void ft_get(int client, char **argv)
{
	int			fd;
	struct stat	stat;
	char 		*data;

	if (ft_checkroot(&argv[1]) == -1)
		return ;
	printf("file [%s] in svrroot\n", argv[1]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return ;
	puts("get opent file");
	if (fstat(fd, &stat) == -1)
		return ;
	puts("get got file stat");
	if ((data = mmap(0, (size_t) stat.st_size, PROT_READ, MAP_FILE | MAP_SHARED, fd, 0)) == MAP_FAILED)
		return ;
	puts("pet got data");
	send(client, data, (size_t) stat.st_size, 0);
}

void ft_put(int client, char **argv)
{
	char *fname;
	int fd;
	char buff[RCVBUFSIZE]; /* Buffer for echo string */
	ssize_t recv_size; /* Size of received message */

	if ((fname = strrchr(argv[1], '/')) == NULL)
		fname = argv[1];
	if ((fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC | O_EVTONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return;
	recv_size = RCVBUFSIZE;
	while (recv_size == RCVBUFSIZE) {
		if ((recv_size = recv(client, buff, RCVBUFSIZE, 0)) < 0)
			printf("recv() failed");
		else {
			write(fd, buff, (size_t) recv_size);
		}
	}
}

void ft_cd(char **argv)
{
	if (ft_checkroot(&argv[1]) == 1)
	{
		if (chdir(argv[1]) == -1)
			printf("\x1b[31mError: could not change to %s\n\x1b[0m", argv[1]);
	}
}

int get_command(char *line, int client)
{
	int re;
	size_t i;
	char *tmp;
	char **tav;

	re = 1;
	tmp = ft_strtrim(line);
	tav = ft_strsplit_fn(line, isspace);
	//todo: loop to choose funct.
	if (strcmp(tav[0], "quite") == 0)
		re = 0;
	if (strcmp(tav[0], "pwd") == 0)
		ft_pwd();
	if (strcmp(tav[0], "cd") == 0)
		ft_cd(tav);
	if (strcmp(tav[0], "ls") == 0)
		ft_ls();
	if (strcmp(tav[0], "put") == 0)
		ft_put(client, tav);
	if (strcmp(tav[0], "get") == 0)
		ft_get(client, tav);
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
		exit_loop = get_command(get_client_data(client), client);
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

void	ft_svr_init_connection(int port)
{
	g_svr_env.svr_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (g_svr_env.svr_id == -1)
		ft_print_exit("Failed to create socket");
	g_svr_env.sock_in.sin_family = AF_INET;
	g_svr_env.sock_in.sin_port = htons((uint16_t)port);
	g_svr_env.sock_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(g_svr_env.svr_id, (const struct sockaddr *) &g_svr_env.sock_in, sizeof(t_tcp_sock_in)) == -1)
		ft_print_exit("failed to bind socket\n");
	if (listen(g_svr_env.svr_id, MAX_CLIENTS) == -1)
		ft_print_exit("socket failed to create listener\n");
}

int main(int ac, char **av)
{
	int	port;

	if (ac < 2 ) {
		printf("please use %s port_num \n\te.g %s 8080\n", av[0], av[0]);
		return (0);
	}
	if (ac == 2)
		port = atoi(av[1]);
	else if ()

		check_port(av[1]) == -1
	g_svr_env.svrroot = get_pwd();

	server_loop(sockid);
	close(sockid);

}

