/*
** xsend.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	<sys/socket.h>

ssize_t		xsend(int s, const void *msg, size_t len, int flags)
{
  ssize_t	i;

  if ((i = send(s, msg, len, flags)) == -1)
    exit(1);
  return (i);
}
