//
// Created by rojones on 2017/07/03.
//

//#include <bits/socket_type.h>
//#include <bits/socket.h>

#include "ft_p_server.h"

t_svr_env g_svr_env = (t_svr_env){-1, -1, NULL};

/*int check_port(const char *str)
{
	while (*str) {
		if (isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return 1;
}*/

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



void ft_cd(char **argv)
{
	if (ft_checkroot(&argv[1]) == 1)
	{
		if (chdir(argv[1]) == -1)
			printf("\x1b[31mError: could not change to %s\n\x1b[0m", argv[1]);
	}
}

void search_builin(t_cmd cmd)
{
	t_builtin_cmd *tmp;

	tmp = g_builtin_cmd;
	while(tmp)
	{
		if (strcmp(cmd.cmd, tmp->cmd) == 0)
			(*tmp->fnc)(cmd);
		tmp++;
	}
	printf("\x1b[mError: Command not recognised'%s'\n\x1b[0m",cmd.cmd);
	ft_send_responce((t_cmd_rsp){502, "Command not recognised"});
}

void chiled()
{
	t_cmd cmd;

	close(g_svr_env.svr_id);
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
	if (perant < 0) {
		printf("wait failed\n");
		exit(1);
	}
	close(g_svr_env.cln_cmd);
}

void server_loop()
{
	pid_t pid;
	t_tcp_sock_in client_sock;
	int clientsize;

	clientsize = sizeof(client_sock);
	while (1) {
		if ((g_svr_env.cln_cmd = accept(g_svr_env.svr_id, (struct sockaddr *) &client_sock, (socklen_t *) &clientsize)) < 0) {
			printf("accept failed\n");
			//exit(1);
		} else {
			printf("got client %s\n", inet_ntoa(client_sock.sin_addr));
			pid = fork();
			if (pid > -1) {
				if (pid == 0)
					chiled();
				else {
					perant(pid);
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

void	ft_svr_init_env(char **av)
{
	if (open(av[2], O_DIRECTORY) == -1)
		ft_print_exit("Failed to set server root dicectory");
	g_svr_env.svrroot = av[2];
	if (check_port(av[3]) == -1)
	{
		printf("please use %s [-root /serverroot] port_num "
					   "\n\te.g %s -root ~/Descktop 8080\n", av[0], av[0]);
		exit(1);
	}
}

int main(int ac, char **av)
{
	int	port;

	if (ac == 2 && check_port(av[1]) == 1)
		port = atoi(av[1]);
	else if (ac == 4 && strcmp(av[1], "-root"))
	{
		ft_svr_init_env(av);
		port = atoi(av[3]);
	}
	else
	{
		printf("please use %s [-root /serverroot] port_num "
					   "\n\te.g %s -root ~/Descktop 8080\n", av[0], av[0]);
		return (0);
	}
	if (g_svr_env.svrroot == NULL)
		g_svr_env.svrroot = get_pwd();
	ft_svr_init_connection(port);
	server_loop();
}

