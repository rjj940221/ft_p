//
// Created by Robert JONES on 2017/07/07.
//

#include "ft_p_server.h"

void ft_put(t_cmd cmd)
{
	/*char *fname;
	int fd;
	char buff[RCVBUFSIZE]; *//* Buffer for echo string *//*
	ssize_t recv_size; *//* Size of received message *//*

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
	}*/
}