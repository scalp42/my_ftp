/*
** xmalloc.c for ftp in /Users/scalp/projs/my_ftp
**
** Made by anthony scalisi
** <scalisia@gmail.com>
**
** Started on  Mon Apr 22 16:03:18 2013 anthony scalisi
** Last update Fri May 03 14:25:37 2013 anthony scalisi
*/

#include	<stdlib.h>

void	*xmalloc(int size)
{
  void	*p;

  p = malloc(size);
  if (p == 0)
    exit (1);
  return (p);
}
