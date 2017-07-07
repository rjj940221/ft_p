//
// Created by Robert JONES on 2017/07/05.
//

#ifndef FT_P_H
# define FT_P_H

//#include <libc.h>
# define RCVBUFSIZE 32
# define FALSE 0
# define TRUE 1

typedef char t_bool;

typedef struct s_command
{
	char *cmd;
	char **av;
}				t_cmd;

typedef struct s_cmd_responce
{
	short code;
	char *msg;
}				t_cmd_rsp;

#endif
