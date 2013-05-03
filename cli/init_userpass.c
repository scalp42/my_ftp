/*
** init_userpass.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdio.h>
#include	<strings.h>
#include	<sys/socket.h>
#include	<unistd.h>
#include	"client.h"


void		init_userpass(client_ftp_t *client_ftp)
{
  int		first;
  int		nb_read;
  char		buffer[1024];
  char		*line;

  first = 0;
  bzero(buffer, 1024);
  for (; (nb_read = xrecv(client_ftp->s, buffer, 1024, 0)); first++)
    {
      clean_buff(buffer, nb_read);
      if (first == 0)
	write(1, "user ?:", 7);
      else if (first == 1)
	write(1, "pass ?:", 7);
      line = get_next_line(0);
      check_line(client_ftp, line, first);
      if (first == 1)
	break;
      bzero(buffer, 1024);
    }
}
