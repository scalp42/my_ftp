/*
** xrecv.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	<sys/socket.h>

ssize_t		xrecv(int s, void *buf, size_t len, int flags)
{
  ssize_t	i;

  if ((i = recv(s, buf, len, flags)) == -1)
    exit(0);
  return (i);
}
