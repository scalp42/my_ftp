/*
** check_option.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"client.h"

void		pwd_opt(client_ftp_t *client_ftp, char *line)
{
  if (strlen(line) == 3)
    printf("%s\n", client_ftp->pwd + 4);
  else
    printf("Command not found\n");
}

void		cd_opt(client_ftp_t *client_ftp, char *line)
{
  char		buff[1024];
  int		i;

  bzero(buff, 1024);
  for (i = 3; line[i] == ' ' && line[i] != '\0'; i++)
    ;
  sprintf(buff, CD, line + i);
  xsend(client_ftp->s, buff, strlen(buff), 0);
  bzero(buff, 1024);
  i = xrecv(client_ftp->s, buff, 1024, 0);
  clean_buff(buff, i);
  printf("%s\n", buff);
  if (strncmp(buff, "250", 3) == 0)
    {
      free(client_ftp->pwd);
      init_pwd(client_ftp);
    }
}

void		ls_opt(client_ftp_t *client_ftp, char __UNUSED__ *line)
{
  open_new_data_connection(client_ftp);
  open_data_connection(client_ftp);
  receiv_ls(client_ftp);
}

void		exit_opt(client_ftp_t *client_ftp, char __UNUSED__ *line)
{
  int		i;
  char		buffer[1024];

  xsend(client_ftp->s, "QUIT\n", 5, 0);
  i = xrecv(client_ftp->s, buffer, 1024, 0);
  clean_buff(buffer, i);
  printf("%s\n", buffer);
  if (strncmp(buffer, "221", 3) == 0)
    client_ftp->to_die = 1;
}

void		check_option(client_ftp_t *client_ftp, char *line)
{
  int		i;
  int		flag;
  option_t	tab[] =
    {
      {"pwd", 3, pwd_opt},
      {"cd", 2, cd_opt},
      {"ls", 2, ls_opt},
      {"exit", 4, exit_opt},
      {"get", 3, retr_opt},
      {"put", 3, stor_opt},
      {0, 0, 0}
    };
  for (i = 0, flag = 0; tab[i].cmd != 0; i++)
    {
      if (strncmp(line, tab[i].cmd, tab[i].len) == 0)
	if (line[strlen(tab[i].cmd)] < 41)
	{
	  tab[i].f(client_ftp, line);
	  flag = 1;
	}
    }
  if (flag == 0 && strlen(line) > 1)
    printf("Command not found\n");
}
