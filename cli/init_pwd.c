/*
** init_pwd.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<string.h>
#include	"client.h"

void		init_pwd(client_ftp_t *client_ftp)
{
  char		buffer[1024];
  int		i;

  bzero(buffer, 1024);
  xsend(client_ftp->s, "PWD\n", 4, 0);
  i = xrecv(client_ftp->s, buffer, 1024, 0);
  clean_buff(buffer, i);
  client_ftp->pwd = strdup(buffer);
}
