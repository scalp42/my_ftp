/*
** receiv_ls.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<strings.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"client.h"

void		receiv_ls(client_ftp_t *client_ftp)
{
  char		buffer[8192];
  int		i;

  bzero(buffer, 8192);
  xsend(client_ftp->s, "LIST\n", 5, 0);
  i = xrecv(client_ftp->s, buffer, 8192, 0);
  clean_buff(buffer, i);
  printf("%s\n", buffer);
  bzero(buffer, 8192);
  while ((i = xrecv(client_ftp->s_data, buffer, 8192, 0)))
    {
      printf("%s\n", buffer);
      bzero(buffer, 8192);
    }
  i = xrecv(client_ftp->s, buffer, 8192, 0);
  clean_buff(buffer, i);
  printf("%s\n", buffer);
  close(client_ftp->s_data);
}
