/*
** xread.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>
#include	<unistd.h>

int     xread(int id_open, void *buffer, int nbytes)
{
  int   nb;

  nb = read(id_open, buffer, nbytes);
  if (nb == -1)
    exit (1);
  return (nb);
}
