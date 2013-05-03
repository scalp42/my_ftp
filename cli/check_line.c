/*
** check_line.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<strings.h>
#include	"client.h"

void		check_line(client_ftp_t *client_ftp, char *line, int first)
{
  char		buff[1024];

  bzero(buff, 1024);
  printf("%s\n", line);
  if (first == 0)
    sprintf(buff, USER, line);
  else
    sprintf(buff, PASS, line);
  free(line);
  printf("%s\n", buff);
  xsend(client_ftp->s, buff, strlen(buff), 0);
}

